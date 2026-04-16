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
#include <process.h>
#include <windows.h>
#define STDERR_FD  2
#define STDOUT_FD  1
#define GET_PID()  _getpid()

// On Windows, ANSI escape codes require ENABLE_VIRTUAL_TERMINAL_PROCESSING.
// _isatty() alone is not sufficient — attempt to enable VT processing and
// return true only if it succeeds.
static bool winEnableAnsiColor(int fd) {
    if (!_isatty(fd)) {
        return false;
    }
    HANDLE h = (fd == 2) ? GetStdHandle(STD_ERROR_HANDLE)
                         : GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD mode = 0;
    if (!GetConsoleMode(h, &mode)) {
        return false;
    }
    if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) {
        return true; // already enabled
    }
    return SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}
#define ISATTY_COLOR(fd) winEnableAnsiColor(fd)

#else
#include <unistd.h>
#define ISATTY_COLOR(fd) (isatty(fd) != 0)
#define GET_PID()  getpid()
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
    bool          is_good;      // cached stream health — avoids internal streambuf lock per write

    // File sink
    explicit LogSink(const std::string &path)
        : stream(nullptr), color_enabled(false), is_good(false)
    {
        file_stream.open(path, std::ios::app);
        if (file_stream.is_open()) {
            stream = &file_stream;
            is_good = true;
        }
        // Files never get color output
    }

    // Console sink
    explicit LogSink(bool use_stderr)
        : stream(use_stderr ? &std::cerr : &std::cout),
          color_enabled(ISATTY_COLOR(use_stderr ? STDERR_FD : STDOUT_FD)),
          is_good(true)
    {}

    bool good() const {
        return is_good;
    }

    void write(const std::string &line) {
        std::lock_guard<std::mutex> lk(mtx);
        if (is_good) {
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
// Default pattern tokens:
//   %Y-%m-%d %H:%M:%S.%e  — timestamp with milliseconds
//   %t                     — thread id (cached thread_local, STB_LOCAL — safe for dlclose)
//   %P                     — process id (cached at construction)
//   %^%l%$                 — level label (with color when tty)
//   %v                     — message
//
// formatLine writes into an existing string (passed by ref) to avoid
// a return-by-value heap allocation on every log call.
// ---------------------------------------------------------------------------
void ZeLogger::formatLine(LogLevel msg_level, const std::string &msg, std::string &out) {
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

    // Thread id — computed once per thread, stored in a thread_local local
    // static inside this non-inline, non-template .cpp function.
    // This produces STB_LOCAL linkage (not STB_GNU_UNIQUE), so dlclose() is unaffected.
    static thread_local const std::string tid_str = [](){
        std::ostringstream ss;
        ss << std::this_thread::get_id();
        return ss.str();
    }();

    const char *label = levelLabel(msg_level);
    const char *color = _sink->color_enabled ? levelColor(msg_level) : "";
    const char *reset = _sink->color_enabled ? AnsiColor::reset()     : "";

    // Write directly into the caller-provided string — no extra allocation.
    out.clear();
    out.reserve(_pattern.size() + msg.size() + 64);

    bool color_span_open = false;

    for (std::size_t i = 0; i < _pattern.size(); ++i) {
        if (_pattern[i] == '%' && i + 1 < _pattern.size()) {
            char tok = _pattern[i + 1];
            switch (tok) {
                case 'Y': {
                    const char *seq = "%Y-%m-%d %H:%M:%S.%e";
                    if (_pattern.compare(i, 20, seq) == 0) {
                        out += ts_full;
                        i += 19;
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
                case 'P':
                    out += std::to_string(GET_PID());
                    ++i;
                    break;
                case '^':
                    out += color;
                    color_span_open = true;
                    ++i;
                    break;
                case 'l':
                    out += label;
                    ++i;
                    break;
                case '$':
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
                    break;
            }
        } else {
            out += _pattern[i];
        }
    }

    if (color_span_open) {
        out += reset;
    }
}

void ZeLogger::write(LogLevel msg_level, const std::string &msg) {
    if (msg_level < _level) {
        return;
    }
    // Reuse a thread_local buffer to avoid a heap allocation per log call.
    // STB_LOCAL linkage (non-inline, non-template .cpp function) — safe for dlclose.
    static thread_local std::string line_buf;
    formatLine(msg_level, msg, line_buf);
    _sink->write(line_buf);
}

void ZeLogger::trace(const std::string &msg)    { write(LogLevel::trace,    msg); }
void ZeLogger::debug(const std::string &msg)    { write(LogLevel::debug,    msg); }
void ZeLogger::info(const std::string &msg)     { write(LogLevel::info,     msg); }
void ZeLogger::warn(const std::string &msg)     { write(LogLevel::warn,     msg); }
void ZeLogger::error(const std::string &msg)    { write(LogLevel::err,      msg); }
void ZeLogger::critical(const std::string &msg) { write(LogLevel::critical, msg); }

} // namespace loader
