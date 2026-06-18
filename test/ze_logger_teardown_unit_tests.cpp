/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// Standalone unit test for the exit-time / teardown use-after-free in
// loader::ZeLogger.  It links ONLY level_zero_utils (the static library that
// contains ze_logger.cpp) -- no loader, no drivers, no validation/tracing
// layers, and none of the SYCL / Unified Runtime stack that originally
// surfaced the bug.
//
// Background
// ----------
// The production crash was a heap-use-after-free: during process exit, a late
// destructor (SYCL shutdown -> UR queue dtor -> zeCommandListHostSynchronize ->
// validation layer) called into ZeLogger AFTER the logger's function-local
// `thread_local std::string` line/tid buffers had already been destroyed by the
// thread-local teardown phase.  formatLine() then wrote into the freed buffer.
//
// Reproducing it without SYCL/UR
// ------------------------------
// thread_local objects are destroyed in REVERSE order of initialization.  If we
// declare a thread_local object whose destructor logs *before* the first real
// log call on a worker thread, then on thread exit:
//   1. ZeLogger's own thread_local buffers (initialized during the first log)
//      are destroyed first, and
//   2. our logging destructor runs last -- emitting a log line into buffers
//      that teardown has already released.
// With the buggy `thread_local std::string` implementation this is a
// heap-use-after-free, caught deterministically when built with -DUSE_ASAN=ON.
// With the POD `thread_local char[]` fix the buffers have trivial destructors
// (their storage survives until the thread's TLS block is freed, after all
// thread_local destructors have run), so the late log call is safe.

#include "gtest/gtest.h"

#include "ze_logger.h"

#include <thread>

namespace {

// A thread_local object whose destructor logs through the shared logger.
struct LogFromThreadLocalDtor {
    loader::ZeLogger *logger;
    ~LogFromThreadLocalDtor() {
        // Runs during the worker thread's thread_local teardown, AFTER the
        // logger's own thread_local line/tid buffers have been destroyed.
        logger->trace("ZeLogger invoked from a thread_local destructor during teardown");
    }
};

// Runs on a dedicated worker thread so that its thread_local destructors fire
// deterministically at thread exit (i.e. at join()), independent of process
// exit ordering.
void workerLogsDuringTeardown(loader::ZeLogger *logger) {
    // Initialized FIRST on this thread -> its destructor runs LAST (after the
    // logger's own thread_local buffers, which are initialized by the warmup
    // log call below).
    thread_local LogFromThreadLocalDtor guard{logger};

    // First real log call: initializes ZeLogger's thread_local line/tid buffers
    // (registered SECOND -> destroyed FIRST).  Exercises every formatLine append
    // path via the pattern set on the logger.
    logger->trace("warmup: initialize the logger's thread_local buffers");

    // Returning ends the thread: the line/tid buffers are torn down first, then
    // `guard`'s destructor logs into them.
}

} // namespace

// Sanity: the logger formats and writes without crashing on a live thread.
TEST(ZeLoggerTeardown, BasicLogDoesNotCrash) {
    loader::ZeLogger logger(/*use_stderr=*/true, loader::LogLevel::trace,
                            "[%Y-%m-%d %H:%M:%S.%e] [tid:%t pid:%P] [%l] %v");
    logger.trace("trace message");
    logger.info("info message");
    logger.warn("warn message");
    SUCCEED();
}

// Regression guard for the exit-time logger UAF.  Builds with -DUSE_ASAN=ON turn
// this into a deterministic detector: the buggy thread_local-std::string logger
// aborts here with heap-use-after-free; the POD-buffer fix completes cleanly.
TEST(ZeLoggerTeardown, LogFromThreadLocalDestructorAfterBufferTeardownIsSafe) {
    loader::ZeLogger logger(/*use_stderr=*/true, loader::LogLevel::trace,
                            "[%Y-%m-%d %H:%M:%S.%e] [tid:%t pid:%P] [%l] %v");

    std::thread worker(workerLogsDuringTeardown, &logger);
    worker.join(); // teardown-time logging happens here

    // Reaching this point without an ASan abort or crash means logging during
    // the thread_local destruction phase did not touch freed memory.
    SUCCEED();
}
