/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_global_timing_state.h
 *
 */

#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <string>

#include "ze_api.h"

namespace validation_layer {

// Per-API host timing aggregation. Modeled on unitrace's ZeFunctionTime
// (tools/unitrace/src/levelzero/ze_collector.h). All values are in nanoseconds
// except call_count.
struct FunctionTime {
    uint64_t total_time = 0;
    uint64_t min_time = 0;
    uint64_t max_time = 0;
    uint64_t call_count = 0;
};

// Engine for the timing checker. Records the host-side duration of every L0 API
// call (the span between its Prologue and Epilogue) and aggregates per-API
// statistics. A single instance is shared by the generated ze/zes/zet/zer
// timing checkers.
//
// The host clock primitive is ported from unitrace's UniTimer
// (tools/unitrace/src/unitimer.h): a high-resolution monotonic counter
// (QueryPerformanceCounter on Windows, CLOCK_MONOTONIC_RAW elsewhere).
class GlobalTimingState {
public:
    static GlobalTimingState &getInstance() {
        static GlobalTimingState instance;
        return instance;
    }

    // Configure output modes from environment variables. Called once when the
    // checker is enabled.
    void configure();

    // Prologue hook: stamp the per-thread start time.
    void recordStart();

    // Epilogue hook: compute the elapsed host time for this call and fold it
    // into the per-API statistics. Optionally emits a live log line.
    void recordEnd(const char *functionName);

    // Teardown reporting.
    void printSummary();
    void writeCsv();

    bool liveLoggingEnabled() const { return liveLogging_; }

    // High-resolution monotonic host timestamp in nanoseconds.
    static uint64_t getHostTimestampNs();

private:
    GlobalTimingState() = default;

    std::mutex stats_mutex_;
    std::map<std::string, FunctionTime> stats_;

    bool liveLogging_ = false;
    std::string csvPath_;

    // Single-slot per-thread start time, matching unitrace's
    // thread_local ze_instance_data.start_time_host. L0 host APIs are not
    // re-entrant through the validation layer, so no stack is required; a
    // value orphaned by another handler's failing Prologue is simply
    // overwritten by the next Prologue.
    static thread_local uint64_t apiStartTime_;
};

} // namespace validation_layer
