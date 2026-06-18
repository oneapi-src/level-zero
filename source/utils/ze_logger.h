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
    // No-op constructor: level=off, no sink, no I/O, no syscalls, no mutex.
    // Use this (or createLogger() with logging disabled) for zero-overhead paths.
    ZeLogger();
    // File sink constructor
    ZeLogger(const std::string &log_path, LogLevel level, const std::string &pattern);
    // Console sink constructor (stderr or stdout)
    ZeLogger(bool use_stderr, LogLevel level, const std::string &pattern);
    ~ZeLogger();

    // Non-copyable and non-movable: a logger owns a sink (stream + mutex) and
    // is always handled through shared_ptr<ZeLogger> (via createLogger()) or as
    // a raw pointer to the process-lifetime noopLogger() instance.  Copying
    // would imply duplicating the sink (nonsensical for console, racy for
    // files); moving is not needed because callers never hold a ZeLogger by
    // value.  Deleting all four documents intent and satisfies Rule-of-Five.
    ZeLogger(const ZeLogger&)            = delete;
    ZeLogger& operator=(const ZeLogger&) = delete;
    ZeLogger(ZeLogger&&)                 = delete;
    ZeLogger& operator=(ZeLogger&&)      = delete;

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

private:
    void write(LogLevel msg_level, const std::string &msg);
    // Formats the log line into a caller-provided fixed buffer (snprintf-style).
    // Returns the total number of bytes the full line needs; if that exceeds
    // `cap` the buffer holds a truncated prefix and the caller must retry with a
    // larger buffer. Uses no owning static state, so it is safe to call during
    // exit-time teardown (no thread_local std::string to outlive its destructor).
    std::size_t formatLine(LogLevel msg_level, const std::string &msg,
                           char *out, std::size_t cap);

    LogLevel _level;
    std::string _pattern;
    std::unique_ptr<LogSink> _sink;
};

// to_string for ze_result_t — declared here, implemented in ze_logger.cpp.
std::string to_string(ze_result_t result);

// Factory: reads ZEL_* env vars and constructs an appropriately configured logger.
std::shared_ptr<ZeLogger> createLogger(const std::string &caller = "Loader");

// A permanently-alive no-op logger instance suitable for use as a raw-pointer
// default in components (e.g. the validation layer) that must never hold a
// shared_ptr across dlclose/process-exit boundaries.
// Level=off, no sink, no I/O.  Safe to call from any thread at any time.
ZeLogger *noopLogger();

} // namespace loader

#endif // ZE_LOGGER_H
