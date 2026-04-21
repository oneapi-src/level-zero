/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "ze_logger.h"
#include "ze_util.h"

#include <cerrno>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <windows.h>
#include <userenv.h>
#include <direct.h>   // _mkdir
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
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
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

// Thread-safe, portable errno-to-string conversion.
// MSVC deprecates strerror() in favour of strerror_s(); POSIX provides strerror_r().
static std::string errnoToString(int err) {
    char buf[256];
#ifdef _WIN32
    strerror_s(buf, sizeof(buf), err);
    return buf;
#elif defined(_GNU_SOURCE)
    // GNU strerror_r returns char* (may or may not use buf)
    const char *result = strerror_r(err, buf, sizeof(buf));
    return result ? result : buf;
#else
    // XSI-compliant strerror_r returns int
    strerror_r(err, buf, sizeof(buf));
    return buf;
#endif
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
    if (s == "warn" || s == "warning") return LogLevel::warn;
    if (s == "err" || s == "error")    return LogLevel::err;
    if (s == "crit" || s == "critical") return LogLevel::critical;
    if (s == "off")      return LogLevel::off;
    return LogLevel::warn; // default
}

// ---------------------------------------------------------------------------
// ZeLogger
// ---------------------------------------------------------------------------
ZeLogger::ZeLogger()
    : _level(LogLevel::off), _pattern(), _sink(nullptr)
{}

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
    if (_sink) _sink->flush();
}

// ---------------------------------------------------------------------------
// Formatting
//
// Default pattern tokens:
//   %Y-%m-%d %H:%M:%S.%e  — timestamp with milliseconds
//   %t                     — thread id (cached thread_local, STB_LOCAL — safe for dlclose)
//   %P                     — process id
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
    if (!_sink || msg_level < _level) {
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

// ---------------------------------------------------------------------------
// to_string for ze_result_t
// ---------------------------------------------------------------------------
std::string to_string(ze_result_t result) {
    if (result == ZE_RESULT_SUCCESS) {
        return "ZE_RESULT_SUCCESS";
    } else if (result == ZE_RESULT_NOT_READY) {
        return "ZE_RESULT_NOT_READY";
    } else if (result == ZE_RESULT_ERROR_UNINITIALIZED) {
        return "ZE_RESULT_ERROR_UNINITIALIZED";
    } else if (result == ZE_RESULT_ERROR_DEVICE_LOST) {
        return "ZE_RESULT_ERROR_DEVICE_LOST";
    } else if (result == ZE_RESULT_ERROR_INVALID_ARGUMENT) {
        return "ZE_RESULT_ERROR_INVALID_ARGUMENT";
    } else if (result == ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY) {
        return "ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY";
    } else if (result == ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY) {
        return "ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY";
    } else if (result == ZE_RESULT_ERROR_MODULE_BUILD_FAILURE) {
        return "ZE_RESULT_ERROR_MODULE_BUILD_FAILURE";
    } else if (result == ZE_RESULT_ERROR_MODULE_LINK_FAILURE) {
        return "ZE_RESULT_ERROR_MODULE_LINK_FAILURE";
    } else if (result == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS) {
        return "ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS";
    } else if (result == ZE_RESULT_ERROR_NOT_AVAILABLE) {
        return "ZE_RESULT_ERROR_NOT_AVAILABLE";
    } else if (result == ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE) {
        return "ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE";
    } else if (result == ZE_RESULT_WARNING_DROPPED_DATA) {
        return "ZE_RESULT_WARNING_DROPPED_DATA";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_VERSION) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_VERSION";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_FEATURE";
    } else if (result == ZE_RESULT_ERROR_INVALID_NULL_HANDLE) {
        return "ZE_RESULT_ERROR_INVALID_NULL_HANDLE";
    } else if (result == ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE) {
        return "ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE";
    } else if (result == ZE_RESULT_ERROR_INVALID_NULL_POINTER) {
        return "ZE_RESULT_ERROR_INVALID_NULL_POINTER";
    } else if (result == ZE_RESULT_ERROR_INVALID_SIZE) {
        return "ZE_RESULT_ERROR_INVALID_SIZE";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_SIZE) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_SIZE";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT";
    } else if (result == ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT) {
        return "ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT";
    } else if (result == ZE_RESULT_ERROR_INVALID_ENUMERATION) {
        return "ZE_RESULT_ERROR_INVALID_ENUMERATION";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION";
    } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT) {
        return "ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT";
    } else if (result == ZE_RESULT_ERROR_INVALID_NATIVE_BINARY) {
        return "ZE_RESULT_ERROR_INVALID_NATIVE_BINARY";
    } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_NAME) {
        return "ZE_RESULT_ERROR_INVALID_GLOBAL_NAME";
    } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_NAME) {
        return "ZE_RESULT_ERROR_INVALID_KERNEL_NAME";
    } else if (result == ZE_RESULT_ERROR_INVALID_FUNCTION_NAME) {
        return "ZE_RESULT_ERROR_INVALID_FUNCTION_NAME";
    } else if (result == ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION) {
        return "ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION";
    } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION) {
        return "ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION";
    } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX) {
        return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX";
    } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE) {
        return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE";
    } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE) {
        return "ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE";
    } else if (result == ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED) {
        return "ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED";
    } else if (result == ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE) {
        return "ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE";
    } else if (result == ZE_RESULT_ERROR_OVERLAPPING_REGIONS) {
        return "ZE_RESULT_ERROR_OVERLAPPING_REGIONS";
    } else if (result == ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET) {
        return "ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET";
    } else if (result == ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE) {
        return "ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE";
    } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_HANDLE) {
        return "ZE_RESULT_ERROR_INVALID_KERNEL_HANDLE";
    } else if (result == ZE_RESULT_ERROR_SURVIVABILITY_MODE_DETECTED) {
        return "ZE_RESULT_ERROR_SURVIVABILITY_MODE_DETECTED";
    } else if (result == ZE_RESULT_ERROR_ADDRESS_NOT_FOUND) {
        return "ZE_RESULT_ERROR_ADDRESS_NOT_FOUND";
    } else if (result == ZE_RESULT_WARNING_ACTION_REQUIRED) {
        return "ZE_RESULT_WARNING_ACTION_REQUIRED";
    } else if (result == ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX) {
        return "ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX";
    } else if (result == ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE) {
        return "ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE";
    } else if (result == ZE_RESULT_EXP_ERROR_REMOTE_DEVICE) {
        return "ZE_RESULT_EXP_ERROR_REMOTE_DEVICE";
    } else if (result == ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE) {
        return "ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE";
    } else if (result == ZE_RESULT_EXP_RTAS_BUILD_RETRY) {
        return "ZE_RESULT_EXP_RTAS_BUILD_RETRY";
    } else if (result == ZE_RESULT_EXP_RTAS_BUILD_DEFERRED) {
        return "ZE_RESULT_EXP_RTAS_BUILD_DEFERRED";
    } else if (result == ZE_RESULT_EXT_RTAS_BUILD_RETRY) {
        return "ZE_RESULT_EXT_RTAS_BUILD_RETRY";
    } else if (result == ZE_RESULT_EXT_RTAS_BUILD_DEFERRED) {
        return "ZE_RESULT_EXT_RTAS_BUILD_DEFERRED";
    } else if (result == ZE_RESULT_EXT_ERROR_OPERANDS_INCOMPATIBLE) {
        return "ZE_RESULT_EXT_ERROR_OPERANDS_INCOMPATIBLE";
    } else if (result == ZE_RESULT_ERROR_UNKNOWN) {
        return "ZE_RESULT_ERROR_UNKNOWN";
    } else {
        return std::to_string(static_cast<int>(result));
    }
}

// ---------------------------------------------------------------------------
// createLogger — reads ZEL_* environment variables and constructs a logger.
// ---------------------------------------------------------------------------
#define LOADER_LOG_FILE           "ze_loader.log"
#define LOADER_LOG_FILE_DIRECTORY ".oneapi_logs"

std::shared_ptr<ZeLogger> createLogger(const std::string &caller) {
    std::string log_directory = getenv_string("ZEL_LOADER_LOG_DIR");
    if (log_directory.empty()) {
        std::string home_dir;
#ifdef _WIN32
        home_dir = getenv_string("USERPROFILE");
        if (home_dir.empty()) {
            auto home_drive = getenv_string("HOMEDRIVE");
            auto home_path  = getenv_string("HOMEPATH");
            if (!home_drive.empty() && !home_path.empty()) {
                home_dir = home_drive + home_path;
            } else {
                home_dir = ".";
            }
        }
        log_directory = home_dir + "\\" + LOADER_LOG_FILE_DIRECTORY;
#else
        home_dir = getenv_string("HOME");
        if (home_dir.empty()) {
            auto *pw = getpwuid(getuid());
            home_dir = (pw && pw->pw_dir) ? std::string(pw->pw_dir) : ".";
        }
        log_directory = home_dir + "/" + LOADER_LOG_FILE_DIRECTORY;
#endif
    }

    auto loader_file = getenv_string("ZEL_LOADER_LOG_FILE");
    if (loader_file.empty()) {
        loader_file = LOADER_LOG_FILE;
    }

#ifdef _WIN32
    std::string full_log_file_path = log_directory + "\\" + loader_file;
#else
    std::string full_log_file_path = log_directory + "/" + loader_file;
#endif

    const bool logging_enabled = getenv_tobool("ZEL_ENABLE_LOADER_LOGGING");
    auto log_level = getenv_string("ZEL_LOADER_LOGGING_LEVEL");
    if (log_level.empty()) {
        log_level = "warn";
    }

    std::string log_pattern = "[%Y-%m-%d %H:%M:%S.%e] [thread-id: %t] [%^%l%$] %v";
    auto custom_pattern = getenv_string("ZEL_LOADER_LOG_PATTERN");
    if (!custom_pattern.empty()) {
        log_pattern = custom_pattern;
    }

    const bool log_console = getenv_tobool("ZEL_LOADER_LOG_CONSOLE");

    // Honour the matrix:
    //   logging_enabled=0, log_console=0  → no-op (level off, no file I/O)
    //   logging_enabled=0, log_console=1  → console (stderr), configured level
    //   logging_enabled=1, log_console=0  → file sink, configured level
    //   logging_enabled=1, log_console=1  → console (stderr), configured level
    if (!logging_enabled && !log_console) {
        // Pure no-op: no sink, no mutex, no isatty() syscall, no pattern string.
        return std::make_shared<ZeLogger>();
    }

    LogLevel level = logLevelFromString(log_level);

    std::shared_ptr<ZeLogger> logger;
    std::string output_dest;
    if (log_console) {
        logger = std::make_shared<ZeLogger>(/*use_stderr=*/true, level, log_pattern);
        output_dest = "stderr (console)";
    } else {
        // Create the full directory path (equivalent to mkdir -p).
#ifdef _WIN32
        // Walk each component and create it if missing.
        for (std::size_t pos = 0; pos <= log_directory.size(); ++pos) {
            if (pos == log_directory.size() ||
                log_directory[pos] == '\\' || log_directory[pos] == '/') {
                if (pos == 0) continue;
                std::string partial = log_directory.substr(0, pos);
                DWORD attrs = GetFileAttributesA(partial.c_str());
                if (attrs == INVALID_FILE_ATTRIBUTES) {
                    if (_mkdir(partial.c_str()) != 0 && errno != EEXIST) {
                        std::cerr << "ze_logger: Failed to create log directory '"
                                  << partial << "': " << errnoToString(errno) << "\n";
                        return std::make_shared<ZeLogger>();
                    }
                } else if (!(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
                    std::cerr << "ze_logger: Log directory path component '"
                              << partial << "' exists but is not a directory\n";
                    return std::make_shared<ZeLogger>();
                }
            }
        }
#else
        // Walk each component and create it if missing.
        for (std::size_t pos = 0; pos <= log_directory.size(); ++pos) {
            if (pos == log_directory.size() || log_directory[pos] == '/') {
                if (pos == 0) continue;
                std::string partial = log_directory.substr(0, pos);
                struct stat st{};
                if (stat(partial.c_str(), &st) != 0) {
                    if (mkdir(partial.c_str(), 0755) != 0 && errno != EEXIST) {
                        std::cerr << "ze_logger: Failed to create log directory '"
                                  << partial << "': " << errnoToString(errno) << "\n";
                        return std::make_shared<ZeLogger>();
                    }
                } else if (!S_ISDIR(st.st_mode)) {
                    std::cerr << "ze_logger: Log directory path component '"
                              << partial << "' exists but is not a directory\n";
                    return std::make_shared<ZeLogger>();
                }
            }
        }
#endif
        logger = std::make_shared<ZeLogger>(full_log_file_path, level, log_pattern);
        output_dest = full_log_file_path;
    }

    // Emit the active configuration as the first log message so the user can
    // confirm what was enabled and where output is going.
    std::string cfg;
    cfg  = caller + " logging enabled:";
    cfg += "\n  ZEL_LOADER_LOG_CONSOLE          : " + std::string(log_console ? "stderr" : "disabled");
    cfg += "\n  ZEL_ENABLE_LOADER_LOGGING        : " + std::string(logging_enabled ? "enabled" : "disabled");
    cfg += "\n  ZEL_LOADER_LOGGING_LEVEL         : " + log_level;
    cfg += "\n  ZEL_LOADER_LOG_DIR               : " + log_directory;
    cfg += "\n  ZEL_LOADER_LOG_FILE              : " + loader_file;
    cfg += "\n  ZEL_LOADER_LOG_PATTERN           : " + log_pattern;
    cfg += "\n  Output                           : " + output_dest;
    logger->info(cfg);

    return logger;
}

} // namespace loader
