/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef ZE_LOGGER_H
#define ZE_LOGGER_H

#include <string>
#include <memory>
#include <mutex>
#include <fstream>
#include <ostream>

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

// Opaque sink type. Implementations live entirely in ze_logger.cpp.
struct LogSink;

// A lightweight, thread-safe, spdlog-free logger.
// All state is in non-static member variables — no STB_GNU_UNIQUE symbols
// are produced by this class.
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

private:
    void write(LogLevel msg_level, const std::string &msg);
    std::string formatLine(LogLevel msg_level, const std::string &msg);

    LogLevel _level;
    std::string _pattern;
    std::unique_ptr<LogSink> _sink;
};

} // namespace loader

#endif // ZE_LOGGER_H
