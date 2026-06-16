/*
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_timing_checker.cpp
 *
 */
#include "zel_timing_checker.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#else
#include <ctime>
#include <unistd.h>
#endif

namespace validation_layer {

constexpr uint64_t NSEC_IN_SEC = 1000000000ULL;

thread_local uint64_t GlobalTimingState::apiStartTime_ = 0;

class timingChecker timing_checker;

uint64_t GlobalTimingState::getHostTimestampNs() {
#if defined(_WIN32)
    static LARGE_INTEGER frequency = {};
    if (frequency.QuadPart == 0) {
        QueryPerformanceFrequency(&frequency);
    }
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    if (frequency.QuadPart == 0) {
        return 0;
    }
    const uint64_t freq = static_cast<uint64_t>(frequency.QuadPart);
    const uint64_t t = static_cast<uint64_t>(ticks.QuadPart);
    // Convert ticks to nanoseconds without integer truncation or overflow by
    // splitting into whole seconds plus the sub-second remainder.
    return (t / freq) * NSEC_IN_SEC + ((t % freq) * NSEC_IN_SEC) / freq;
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0) {
        return 0;
    }
    return static_cast<uint64_t>(ts.tv_sec) * NSEC_IN_SEC + static_cast<uint64_t>(ts.tv_nsec);
#endif
}

void GlobalTimingState::configure() {
    liveLogging_ = getenv_tobool("ZEL_TIMING_CHECKER_LIVE");
    csvPath_ = getenv_string("ZEL_TIMING_CHECKER_CSV");
}

void GlobalTimingState::recordStart() {
    apiStartTime_ = getHostTimestampNs();
}

void GlobalTimingState::recordEnd(const char *functionName) {
    const uint64_t end = getHostTimestampNs();
    // A start time of 0 means the matching Prologue did not run on this thread
    // (e.g. another handler short-circuited the call); skip it.
    if (apiStartTime_ == 0 || end < apiStartTime_) {
        return;
    }
    const uint64_t elapsed = end - apiStartTime_;
    apiStartTime_ = 0;

    {
        const std::lock_guard<std::mutex> lock(stats_mutex_);
        auto it = stats_.find(functionName);
        if (it == stats_.end()) {
            FunctionTime stat;
            stat.total_time = elapsed;
            stat.min_time = elapsed;
            stat.max_time = elapsed;
            stat.call_count = 1;
            stats_.insert({functionName, stat});
        } else {
            it->second.total_time += elapsed;
            it->second.call_count += 1;
            if (elapsed < it->second.min_time) {
                it->second.min_time = elapsed;
            }
            if (elapsed > it->second.max_time) {
                it->second.max_time = elapsed;
            }
        }
    }

    // Emitted directly to stderr (not via the loader logger) so the checker's
    // output does not depend on ZEL_ENABLE_LOADER_LOGGING / ZEL_LOADER_LOGGING_LEVEL
    // and does not require enabling API-call trace logging.
    if (liveLogging_) {
        std::cerr << "[timing] " << functionName << " " << elapsed << " ns\n";
    }
}

void GlobalTimingState::printSummary() {
    std::vector<std::pair<std::string, FunctionTime>> entries;
    {
        const std::lock_guard<std::mutex> lock(stats_mutex_);
        entries.assign(stats_.begin(), stats_.end());
    }
    if (entries.empty()) {
        return;
    }

    // Sort by share of total host time, highest first.
    std::sort(entries.begin(), entries.end(),
              [](const std::pair<std::string, FunctionTime> &a,
                 const std::pair<std::string, FunctionTime> &b) {
                  return a.second.total_time > b.second.total_time;
              });

    uint64_t grandTotal = 0;
    for (const auto &entry : entries) {
        grandTotal += entry.second.total_time;
    }

    std::ostringstream out;
    out << "\n==== Level Zero Host API Timing (ns) ====\n";
    out << std::left << std::setw(48) << "Function" << std::right << std::setw(10) << "Calls"
        << std::setw(16) << "Total" << std::setw(14) << "Min" << std::setw(14) << "Max"
        << std::setw(14) << "Avg" << std::setw(9) << "%" << "\n";
    for (const auto &entry : entries) {
        const FunctionTime &t = entry.second;
        const uint64_t avg = t.call_count ? (t.total_time / t.call_count) : 0;
        const double pct = grandTotal ? (100.0 * static_cast<double>(t.total_time) / static_cast<double>(grandTotal)) : 0.0;
        std::ostringstream pctStr;
        pctStr << std::fixed << std::setprecision(2) << pct << "%";
        out << std::left << std::setw(48) << entry.first << std::right << std::setw(10)
            << t.call_count << std::setw(16) << t.total_time << std::setw(14) << t.min_time
            << std::setw(14) << t.max_time << std::setw(14) << avg << std::setw(9) << pctStr.str() << "\n";
    }
    // Emitted directly to stderr (not via the loader logger) so the summary is
    // produced whenever the checker is enabled, independent of the loader logging
    // configuration.
    std::cerr << out.str();
}

void GlobalTimingState::writeCsv() {
    if (csvPath_.empty()) {
        return;
    }

    std::vector<std::pair<std::string, FunctionTime>> entries;
    {
        const std::lock_guard<std::mutex> lock(stats_mutex_);
        entries.assign(stats_.begin(), stats_.end());
    }

    // Sort by share of total host time, highest first.
    std::sort(entries.begin(), entries.end(),
              [](const std::pair<std::string, FunctionTime> &a,
                 const std::pair<std::string, FunctionTime> &b) {
                  return a.second.total_time > b.second.total_time;
              });

    uint64_t grandTotal = 0;
    for (const auto &entry : entries) {
        grandTotal += entry.second.total_time;
    }

    // Append the process id so concurrent processes do not clobber each other,
    // matching the System Resource Tracker checker.
#if defined(_WIN32)
    const unsigned long pid = static_cast<unsigned long>(GetCurrentProcessId());
#else
    const unsigned long pid = static_cast<unsigned long>(getpid());
#endif
    std::string uniquePath = csvPath_;
    const auto dot = uniquePath.find_last_of('.');
    if (dot == std::string::npos) {
        uniquePath += "_" + std::to_string(pid) + ".csv";
    } else {
        uniquePath = uniquePath.substr(0, dot) + "_" + std::to_string(pid) + uniquePath.substr(dot);
    }

    std::ofstream csv(uniquePath, std::ios::out | std::ios::trunc);
    if (!csv.is_open()) {
        std::cerr << "[timing] Failed to open timing CSV file: " << uniquePath << "\n";
        return;
    }

    csv << "Function,Calls,TotalNs,MinNs,MaxNs,AvgNs,%\n";
    for (const auto &entry : entries) {
        const FunctionTime &t = entry.second;
        const uint64_t avg = t.call_count ? (t.total_time / t.call_count) : 0;
        const double pct = grandTotal ? (100.0 * static_cast<double>(t.total_time) / static_cast<double>(grandTotal)) : 0.0;
        csv << entry.first << "," << t.call_count << "," << t.total_time << "," << t.min_time
            << "," << t.max_time << "," << avg << "," << std::fixed << std::setprecision(2) << pct << "\n";
    }
    csv.flush();
    csv.close();

    std::cerr << "[timing] CSV written: " << uniquePath << "\n";
}

timingChecker::timingChecker() {
    enabletiming = getenv_tobool("ZEL_ENABLE_TIMING_CHECKER");
    if (enabletiming) {
        GlobalTimingState::getInstance().configure();
        timingChecker::ZEtimingChecker *zeChecker = new timingChecker::ZEtimingChecker;
        timingChecker::ZEStimingChecker *zesChecker = new timingChecker::ZEStimingChecker;
        timingChecker::ZETtimingChecker *zetChecker = new timingChecker::ZETtimingChecker;
        timingChecker::ZERtimingChecker *zerChecker = new timingChecker::ZERtimingChecker;
        timing_checker.zeValidation = zeChecker;
        timing_checker.zetValidation = zetChecker;
        timing_checker.zesValidation = zesChecker;
        timing_checker.zerValidation = zerChecker;
        // Register at the front so the timing checker's Prologue/Epilogue run first.
        // The validation dispatch aborts the Epilogue loop if any handler returns a
        // non-success result, so running first ensures every call is measured even
        // when a later handler reports an error.
        auto &handlers = validation_layer::context.getInstance().validationHandlers;
        handlers.insert(handlers.begin(), &timing_checker);
    }
}

timingChecker::~timingChecker() {
    if (enabletiming) {
        GlobalTimingState::getInstance().printSummary();
        GlobalTimingState::getInstance().writeCsv();
        delete timing_checker.zeValidation;
        delete timing_checker.zetValidation;
        delete timing_checker.zesValidation;
        delete timing_checker.zerValidation;
    }
}

} // namespace validation_layer
