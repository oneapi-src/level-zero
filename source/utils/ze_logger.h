/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef ZE_LOGGER_H
#define ZE_LOGGER_H

#include <memory>
#include <string>
#include <mutex>
#include <fstream>
#include <ostream>

#include "ze_api.h"

namespace loader {

// Log level enum
enum class LogLevel {
    trace    = 0,
    debug    = 1,
    info     = 2,
    warn     = 3,
    err      = 4,
    critical = 5,
    off      = 6,
};

LogLevel logLevelFromString(const std::string &s);

// Console sink selector used by createLogger().
enum class Console {
    out_stdout,
    out_stderr
};

// Opaque sink type. Implementations live entirely in ze_logger.cpp.
struct LogSink;

// A lightweight, thread-safe logger.
// All state is in non-static member variables — no STB_GNU_UNIQUE symbols
// are produced by this class so it can be unloaded by dlclose().
class ZeLogger {
public:
    // File sink constructor
    ZeLogger(const std::string &log_path, LogLevel level, const std::string &pattern);
    // Console sink constructor (stderr or stdout)
    ZeLogger(bool use_stderr, LogLevel level, const std::string &pattern);
    ~ZeLogger();

    void setLevel(LogLevel level);
    LogLevel getLevel() const;

    void trace(const std::string &msg);
    void debug(const std::string &msg);
    void info(const std::string &msg);
    void warn(const std::string &msg);
    void error(const std::string &msg);
    void critical(const std::string &msg);

    void flush();

    // Convenience aliases matching the legacy Logger API used by callers.
    void log_trace(const std::string &msg)       { trace(msg); }
    void log_debug(const std::string &msg)        { debug(msg); }
    void log_info(const std::string &msg)         { info(msg); }
    void log_warning(const std::string &msg)      { warn(msg); }
    void log_error(const std::string &msg)        { error(msg); }
    void log_fatal(const std::string &msg)        { critical(msg); }
    void log_performance(const std::string &msg)  { warn("[performance] " + msg); }

    // When true, callers may mirror certain messages to stdout/stderr.
    // Defaulted to true so init code can read it before explicitly disabling.
    bool log_to_console = true;

private:
    void write(LogLevel msg_level, const std::string &msg);
    void formatLine(LogLevel msg_level, const std::string &msg, std::string &out);

    LogLevel _level;
    std::string _pattern;
    std::unique_ptr<LogSink> _sink;
};

// to_string for ze_result_t — declared here, implemented in ze_logger.cpp.
std::string to_string(ze_result_t result);

// Factory: reads ZEL_* env vars and constructs an appropriately configured logger.
std::shared_ptr<ZeLogger> createLogger(const std::string &caller = "Loader");

} // namespace loader

#endif // ZE_LOGGER_H
