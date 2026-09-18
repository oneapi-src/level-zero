/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// Unit tests for the ZEL_LOADER_LOG_FILE filename-pattern expansion implemented
// in source/utils/ze_logger.cpp (baseNameFromPath / sanitizeFileNameComponent /
// expandLogFilePattern). They link ONLY level_zero_utils -- no loader, drivers,
// or layers -- so they are true unit tests independent of any hardware.

#include <gtest/gtest.h>

#include "ze_logger.h"

#include <regex>
#include <string>

#if defined(_WIN32)
#include <process.h>
#define TEST_GET_PID() _getpid()
#else
#include <unistd.h>
#define TEST_GET_PID() getpid()
#endif

namespace {

std::string currentPidString() {
    return std::to_string(static_cast<long long>(TEST_GET_PID()));
}

// -----------------------------------------------------------------------------
// baseNameFromPath
// -----------------------------------------------------------------------------

TEST(ZeLoggerBaseNameFromPath, GivenNoSeparatorThenReturnsInputUnchanged) {
    EXPECT_EQ(std::string("ze_loader.log"), loader::baseNameFromPath("ze_loader.log"));
}

TEST(ZeLoggerBaseNameFromPath, GivenForwardSlashPathThenReturnsLastComponent) {
    EXPECT_EQ(std::string("app.exe"), loader::baseNameFromPath("/usr/bin/app.exe"));
}

TEST(ZeLoggerBaseNameFromPath, GivenBackslashPathThenReturnsLastComponent) {
    EXPECT_EQ(std::string("app.exe"), loader::baseNameFromPath("C:\\Program Files\\app.exe"));
}

TEST(ZeLoggerBaseNameFromPath, GivenTrailingSeparatorThenReturnsEmpty) {
    EXPECT_EQ(std::string(""), loader::baseNameFromPath("/usr/bin/"));
}

// -----------------------------------------------------------------------------
// sanitizeFileNameComponent
// -----------------------------------------------------------------------------

TEST(ZeLoggerSanitizeFileNameComponent, GivenEmptyThenReturnsProcessPlaceholder) {
    EXPECT_EQ(std::string("process"), loader::sanitizeFileNameComponent(""));
}

TEST(ZeLoggerSanitizeFileNameComponent, GivenPlainNameThenReturnsUnchanged) {
    EXPECT_EQ(std::string("app_name-1.2"), loader::sanitizeFileNameComponent("app_name-1.2"));
}

TEST(ZeLoggerSanitizeFileNameComponent, GivenPathHostileCharactersThenReplacedWithUnderscore) {
    EXPECT_EQ(std::string("a_b_c_d_e_f_g_h_i"),
              loader::sanitizeFileNameComponent("a<b>c:d\"e/f\\g|h?i"));
    EXPECT_EQ(std::string("star_"), loader::sanitizeFileNameComponent("star*"));
}

TEST(ZeLoggerSanitizeFileNameComponent, GivenControlCharacterThenReplacedWithUnderscore) {
    EXPECT_EQ(std::string("a_b"), loader::sanitizeFileNameComponent(std::string("a\x01") + "b"));
}

// -----------------------------------------------------------------------------
// expandLogFilePattern
// -----------------------------------------------------------------------------

TEST(ZeLoggerExpandLogFilePattern, GivenNoTokenThenReturnsUnchanged) {
    EXPECT_EQ(std::string("ze_loader.log"), loader::expandLogFilePattern("ze_loader.log"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenEmptyThenReturnsEmpty) {
    EXPECT_EQ(std::string(""), loader::expandLogFilePattern(""));
}

TEST(ZeLoggerExpandLogFilePattern, GivenDoublePercentThenCollapsedToSinglePercent) {
    EXPECT_EQ(std::string("a%b"), loader::expandLogFilePattern("a%%b"));
    EXPECT_EQ(std::string("100%"), loader::expandLogFilePattern("100%%"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenPidTokenThenReplacedWithProcessId) {
    const std::string pid = currentPidString();
    EXPECT_EQ("ze_loader-" + pid + ".log", loader::expandLogFilePattern("ze_loader-%P.log"));
    EXPECT_EQ(pid + pid, loader::expandLogFilePattern("%P%P"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenNameTokenThenReplacedWithSafeNonEmptyComponent) {
    const std::string name = loader::expandLogFilePattern("%N");
    EXPECT_FALSE(name.empty());
    // The expansion is a single sanitized filename component: no path
    // separators and no other path-hostile characters survive.
    EXPECT_EQ(std::string::npos, name.find('/'));
    EXPECT_EQ(std::string::npos, name.find('\\'));
    EXPECT_EQ(std::string::npos, name.find_first_of("<>:\"|?*"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenTimestampTokenThenMatchesExpectedFormat) {
    const std::string ts = loader::expandLogFilePattern("%T");
    EXPECT_TRUE(std::regex_match(ts, std::regex("[0-9]{8}-[0-9]{6}")))
        << "unexpected timestamp: " << ts;
}

TEST(ZeLoggerExpandLogFilePattern, GivenUnknownTokenThenKeptVerbatim) {
    // An unrecognised token letter is preserved together with its '%'.
    EXPECT_EQ(std::string("a%Xb"), loader::expandLogFilePattern("a%Xb"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenTrailingLonePercentThenKeptVerbatim) {
    // A '%' with no following character cannot start a token and is emitted as-is.
    EXPECT_EQ(std::string("log%"), loader::expandLogFilePattern("log%"));
}

TEST(ZeLoggerExpandLogFilePattern, GivenCombinedTokensThenAllExpanded) {
    const std::string result = loader::expandLogFilePattern("%N-%T-%P.log");
    const std::string pid = currentPidString();

    // Ends with the pid token expansion followed by the literal suffix.
    const std::string suffix = "-" + pid + ".log";
    ASSERT_GE(result.size(), suffix.size());
    EXPECT_EQ(suffix, result.substr(result.size() - suffix.size()));

    // Contains an embedded timestamp somewhere in the middle.
    EXPECT_TRUE(std::regex_search(result, std::regex("[0-9]{8}-[0-9]{6}")))
        << "no timestamp in: " << result;
}

} // namespace
