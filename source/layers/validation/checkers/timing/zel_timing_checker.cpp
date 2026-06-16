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
    return static_cast<uint64_t>(ticks.QuadPart) * (NSEC_IN_SEC / static_cast<uint64_t>(frequency.QuadPart));
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

    if (liveLogging_ && context.logger != nullptr) {
        context.logger->log_info("[timing] " + std::string(functionName) + " " +
                                 std::to_string(elapsed) + " ns");
    }
}

void GlobalTimingState::printSummary() {
    std::vector<std::pair<std::string, FunctionTime>> entries;
    {
        const std::lock_guard<std::mutex> lock(stats_mutex_);
        entries.assign(stats_.begin(), stats_.end());
    }
    if (entries.empty() || context.logger == nullptr) {
        return;
    }

    std::sort(entries.begin(), entries.end(),
              [](const std::pair<std::string, FunctionTime> &a,
                 const std::pair<std::string, FunctionTime> &b) {
                  return a.second.total_time > b.second.total_time;
              });

    std::ostringstream out;
    out << "\n==== Level Zero Host API Timing (ns) ====\n";
    out << std::left << std::setw(48) << "Function" << std::right << std::setw(10) << "Calls"
        << std::setw(16) << "Total" << std::setw(14) << "Min" << std::setw(14) << "Max"
        << std::setw(14) << "Avg" << "\n";
    for (const auto &entry : entries) {
        const FunctionTime &t = entry.second;
        const uint64_t avg = t.call_count ? (t.total_time / t.call_count) : 0;
        out << std::left << std::setw(48) << entry.first << std::right << std::setw(10)
            << t.call_count << std::setw(16) << t.total_time << std::setw(14) << t.min_time
            << std::setw(14) << t.max_time << std::setw(14) << avg << "\n";
    }
    context.logger->log_info(out.str());
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
        if (context.logger != nullptr) {
            context.logger->log_error("Failed to open timing CSV file: " + uniquePath);
        }
        return;
    }

    csv << "Function,Calls,TotalNs,MinNs,MaxNs,AvgNs\n";
    for (const auto &entry : entries) {
        const FunctionTime &t = entry.second;
        const uint64_t avg = t.call_count ? (t.total_time / t.call_count) : 0;
        csv << entry.first << "," << t.call_count << "," << t.total_time << "," << t.min_time
            << "," << t.max_time << "," << avg << "\n";
    }
    csv.flush();
    csv.close();

    if (context.logger != nullptr) {
        context.logger->log_info("Timing checker CSV written: " + uniquePath);
    }
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
        validation_layer::context.getInstance().validationHandlers.push_back(&timing_checker);
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
