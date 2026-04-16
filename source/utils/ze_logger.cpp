/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "ze_logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#ifdef _WIN32
#include <io.h>
#define ISATTY(fd) _isatty(fd)
#define STDERR_FD  2
#define STDOUT_FD  1
#else
#include <unistd.h>
#define ISATTY(fd) isatty(fd)
#define STDERR_FD  STDERR_FILENO
#define STDOUT_FD  STDOUT_FILENO
#endif

namespace loader {

// ---------------------------------------------------------------------------
// ANSI color codes — only emitted when writing to a tty.
// ---------------------------------------------------------------------------
namespace {

struct AnsiColor {
    static const char *reset()    { return "\033[0m";  }
    static const char *trace()    { return "\033[37m";  }  // white
    static const char *debug()    { return "\033[36m";  }  // cyan
    static const char *info()     { return "\033[32m";  }  // green
    static const char *warn()     { return "\033[33m";  }  // yellow
    static const char *err()      { return "\033[31m";  }  // red
    static const char *critical() { return "\033[35m";  }  // magenta
};

const char *levelLabel(LogLevel l) {
    switch (l) {
        case LogLevel::trace:    return "trace";
        case LogLevel::debug:    return "debug";
        case LogLevel::info:     return "info";
        case LogLevel::warn:     return "warn";
        case LogLevel::err:      return "error";
        case LogLevel::critical: return "critical";
        default:                 return "off";
    }
}

const char *levelColor(LogLevel l) {
    switch (l) {
        case LogLevel::trace:    return AnsiColor::trace();
        case LogLevel::debug:    return AnsiColor::debug();
        case LogLevel::info:     return AnsiColor::info();
        case LogLevel::warn:     return AnsiColor::warn();
        case LogLevel::err:      return AnsiColor::err();
        case LogLevel::critical: return AnsiColor::critical();
        default:                 return "";
    }
}

} // anonymous namespace

// ---------------------------------------------------------------------------
// LogSink — one per ZeLogger instance, owns the output stream and its mutex.
// ---------------------------------------------------------------------------
struct LogSink {
    std::ostream *stream;       // non-owning for console, owning via file_stream
    std::ofstream file_stream;  // only open for file sinks
    std::mutex    mtx;
    bool          color_enabled;

    // File sink
    explicit LogSink(const std::string &path)
        : stream(nullptr), color_enabled(false)
    {
        file_stream.open(path, std::ios::app);
        if (file_stream.is_open()) {
            stream = &file_stream;
        }
        // Files never get color output
    }

    // Console sink
    explicit LogSink(bool use_stderr)
        : stream(use_stderr ? &std::cerr : &std::cout),
          color_enabled(ISATTY(use_stderr ? STDERR_FD : STDOUT_FD) != 0)
    {}

    bool good() const {
        return stream != nullptr && stream->good();
    }

    void write(const std::string &line) {
        std::lock_guard<std::mutex> lk(mtx);
        if (stream && stream->good()) {
            *stream << line << '\n';
        }
    }

    void flush() {
        std::lock_guard<std::mutex> lk(mtx);
        if (stream) {
            stream->flush();
        }
    }
};

// ---------------------------------------------------------------------------
// LogLevel helpers
// ---------------------------------------------------------------------------
LogLevel logLevelFromString(const std::string &s) {
    if (s == "trace")    return LogLevel::trace;
    if (s == "debug")    return LogLevel::debug;
    if (s == "info")     return LogLevel::info;
    if (s == "warn")     return LogLevel::warn;
    if (s == "error")    return LogLevel::err;
    if (s == "critical") return LogLevel::critical;
    return LogLevel::warn; // default
}

// ---------------------------------------------------------------------------
// ZeLogger
// ---------------------------------------------------------------------------
ZeLogger::ZeLogger(const std::string &log_path, LogLevel level, const std::string &pattern)
    : _level(level), _pattern(pattern), _sink(new LogSink(log_path))
{
    if (!_sink->good()) {
        std::cerr << "ze_logger: Unable to open log file: " << log_path << "\n";
        // Sink remains but writes will silently no-op via stream->good() check.
    }
}

ZeLogger::ZeLogger(bool use_stderr, LogLevel level, const std::string &pattern)
    : _level(level), _pattern(pattern), _sink(new LogSink(use_stderr))
{}

ZeLogger::~ZeLogger() {
    flush();
}

void ZeLogger::setLevel(LogLevel level) {
    _level = level;
}

LogLevel ZeLogger::getLevel() const {
    return _level;
}

void ZeLogger::flush() {
    _sink->flush();
}

// ---------------------------------------------------------------------------
// Formatting
//
// Default pattern tokens (mirrors spdlog's default used in the project):
//   %Y-%m-%d %H:%M:%S.%e  — timestamp with milliseconds
//   %t                     — thread id (decimal)
//   %^%l%$                 — level label (with color when tty)
//   %v                     — message
//
// We implement only the tokens actually used by the project's log_pattern.
// Unknown tokens are passed through unchanged.
// ---------------------------------------------------------------------------
std::string ZeLogger::formatLine(LogLevel msg_level, const std::string &msg) {
    // Build timestamp: YYYY-MM-DD HH:MM:SS.mmm
    auto now   = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    auto ms    = std::chrono::duration_cast<std::chrono::milliseconds>(
                     now.time_since_epoch()) % 1000;

    std::tm tm_buf{};
#ifdef _WIN32
    localtime_s(&tm_buf, &now_t);
#else
    localtime_r(&now_t, &tm_buf);
#endif

    char ts[32];
    std::strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", &tm_buf);

    char ts_full[40];
    std::snprintf(ts_full, sizeof(ts_full), "%s.%03lld", ts,
                  static_cast<long long>(ms.count()));

    // Thread id as decimal string
    std::ostringstream tid_ss;
    tid_ss << std::this_thread::get_id();
    std::string tid_str = tid_ss.str();

    const char *label = levelLabel(msg_level);
    const char *color = _sink->color_enabled ? levelColor(msg_level) : "";
    const char *reset = _sink->color_enabled ? AnsiColor::reset()     : "";

    // Walk the pattern and substitute tokens
    std::string out;
    out.reserve(_pattern.size() + msg.size() + 64);

    bool color_span_open = false;

    for (std::size_t i = 0; i < _pattern.size(); ++i) {
        if (_pattern[i] == '%' && i + 1 < _pattern.size()) {
            char tok = _pattern[i + 1];
            switch (tok) {
                case 'Y': {
                    // Start of %Y-%m-%d %H:%M:%S.%e sequence — emit the full timestamp
                    // and skip all the formatting chars that follow (%Y-%m-%d %H:%M:%S.%e)
                    // We detect this by checking if the pattern has the full sequence.
                    // For robustness we just emit the pre-computed ts_full and
                    // advance past the known literal pattern.
                    const char *seq = "%Y-%m-%d %H:%M:%S.%e";
                    if (_pattern.compare(i, 20, seq) == 0) {
                        out += ts_full;
                        i += 19; // skip the rest of the sequence (loop will ++i)
                    } else {
                        out += '%';
                        out += tok;
                        ++i;
                    }
                    break;
                }
                case 't':
                    out += tid_str;
                    ++i;
                    break;
                case '^':
                    // Begin colored level region
                    out += color;
                    color_span_open = true;
                    ++i;
                    break;
                case 'l':
                    out += label;
                    ++i;
                    break;
                case '$':
                    // End colored level region
                    out += reset;
                    color_span_open = false;
                    ++i;
                    break;
                case 'v':
                    out += msg;
                    ++i;
                    break;
                default:
                    out += '%';
                    // don't advance i; the next char will be handled naturally
                    break;
            }
        } else {
            out += _pattern[i];
        }
    }

    if (color_span_open) {
        out += reset; // safety: close any unclosed color span
    }

    return out;
}

void ZeLogger::write(LogLevel msg_level, const std::string &msg) {
    if (msg_level < _level) {
        return;
    }
    _sink->write(formatLine(msg_level, msg));
}

void ZeLogger::trace(const std::string &msg)    { write(LogLevel::trace,    msg); }
void ZeLogger::debug(const std::string &msg)    { write(LogLevel::debug,    msg); }
void ZeLogger::info(const std::string &msg)     { write(LogLevel::info,     msg); }
void ZeLogger::warn(const std::string &msg)     { write(LogLevel::warn,     msg); }
void ZeLogger::error(const std::string &msg)    { write(LogLevel::err,      msg); }
void ZeLogger::critical(const std::string &msg) { write(LogLevel::critical, msg); }

} // namespace loader
