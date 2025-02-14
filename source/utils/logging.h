/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef level_zero_loader_LOGGING_HPP
#define level_zero_loader_LOGGING_HPP

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#define LOADER_LOG_FILE "ze_loader.log"
#define LOADER_LOG_FILE_DIRECTORY ".oneapi_logs"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include "ze_api.h"
#include "ze_util.h"

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif // __linux__

namespace loader {

std::string to_string(const ze_result_t result);

enum class Console {
  out_stdout,
  out_stderr
};

class Logger {
public:
  Logger(std::string logger_name, std::string filename, std::string log_level, bool logging_enabled_env, std::string format = "") {
    if (logging_enabled_env) {
      logging_enabled = logging_enabled_env;
      try {
        _logger = spdlog::basic_logger_st(logger_name, filename);
      } catch (spdlog::spdlog_ex &exception) {
        std::cerr << "Unable to create log file: " << exception.what() << "\n";
        logging_enabled = false;
        return;
      }

      if (!format.empty()) {
        _logger->set_pattern(format);
      }

      setLogLevel(log_level);
    }
  }

  Logger(std::string logger_name, Console out, std::string log_level, bool logging_enabled_env, std::string format = "") {
    if (logging_enabled_env) {
      logging_enabled = logging_enabled_env;
      try {
        if (out == Console::out_stdout) {
          auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
          _logger = std::make_shared<spdlog::logger>(logger_name, std::move(sink));
        } else if (out == Console::out_stderr) {
          auto sink = std::make_shared<spdlog::sinks::ansicolor_stderr_sink_mt>();
          _logger = std::make_shared<spdlog::logger>(logger_name, std::move(sink));
        } else {
          std::cerr << "Invalid console output specified\n";
          logging_enabled = false;
          return;
        }
      } catch (spdlog::spdlog_ex &exception) {
        std::cerr << "Unable to create log stdout logger " << exception.what() << "\n";
        logging_enabled = false;
        return;
      }

      if (!format.empty()) {
        _logger->set_pattern(format);
      }

      setLogLevel(log_level);
    }
  }

  ~Logger() {
    if (!logging_enabled)
      return;
    _logger->flush();
  }

  void set_level(spdlog::level::level_enum log_level){
    if (!logging_enabled)
      return;
    _logger->set_level(log_level);
  }

  void log_trace(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->trace(msg);
  }
  void log_debug(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->debug(msg);
  }
  void log_info(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->info(msg);
  }
  void log_warning(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->warn(msg);
  }
  void log_error(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->error(msg);
  }
  void log_fatal(std::string msg) {
    if (!logging_enabled)
      return;
    _logger->critical(msg);
  }

  std::shared_ptr<spdlog::logger> get_base_logger(){
    return _logger;
  }

bool log_to_console = true;
bool logging_enabled = false;
private:
  void setLogLevel(std::string log_level) {
    // validate log level
    if ("trace" == log_level) {
      _logger->set_level(spdlog::level::trace);
    } else if ("debug" == log_level) {
      _logger->set_level(spdlog::level::debug);
    } else if ("info" == log_level) {
      _logger->set_level(spdlog::level::info);
    } else if ("warn" == log_level) {
      _logger->set_level(spdlog::level::warn);
    } else if ("error" == log_level) {
      _logger->set_level(spdlog::level::err);
    } else if ("critical" == log_level) {
      _logger->set_level(spdlog::level::critical);
    } else if ("off" == log_level) {
      _logger->set_level(spdlog::level::off);
    } else {
      _logger->warn("Invalid logging level set: ", log_level);
    }

    spdlog::flush_on(spdlog::level::trace);
  }

  std::shared_ptr<spdlog::logger> _logger = nullptr;
};

inline std::shared_ptr<Logger> createLogger() {
  std::shared_ptr<Logger> zel_logger;

  auto log_directory = getenv_string("ZEL_LOADER_LOG_DIR");
  if (log_directory.empty()) {
      std::string home_dir;
#ifdef _WIN32
      home_dir = getenv_string("USERPROFILE");
      if (home_dir == ""){
          auto home_drive = getenv_string("HOMEDRIVE");
          auto home_path = getenv_string("HOMEPATH");
          if ((home_drive != "") && (home_path != "")) {
              home_dir = home_drive + home_path;
          } else {
              home_dir = ".";
          }
      }
      log_directory = home_dir + "\\" + LOADER_LOG_FILE_DIRECTORY;
#else
      home_dir = getenv_string("HOME");

      if (home_dir == "") {
          auto pwdir = getpwuid(getuid())->pw_dir;
          home_dir = (pwdir == NULL) ? "." : std::string(pwdir);
      }
      log_directory = home_dir + "/" + LOADER_LOG_FILE_DIRECTORY;
#endif
  }
  auto loader_file = getenv_string("ZEL_LOADER_LOG_FILE");
  if (loader_file.empty()){
      loader_file = LOADER_LOG_FILE;
  } else {
      auto log_depr_msg = "ZEL_LOADER_LOG_FILE will be deprecated in a future release";
      std::cout << log_depr_msg << std::endl;
  }

  std::string full_log_file_path = "";
#ifdef _WIN32
  full_log_file_path = log_directory + "\\" + loader_file;
#else
  full_log_file_path = log_directory + "/" + loader_file;
#endif
  auto logging_enabled = getenv_tobool( "ZEL_ENABLE_LOADER_LOGGING" );
  auto log_level = getenv_string("ZEL_LOADER_LOGGING_LEVEL");
  auto log_console = getenv_tobool("ZEL_LOADER_LOG_CONSOLE");

  if (log_level.empty()) {
      log_level = "warn";
  }

  if (!log_console) {
      zel_logger =  std::make_shared<Logger>("ze_loader", full_log_file_path, log_level, logging_enabled);
  } else {
      zel_logger =  std::make_shared<Logger>("ze_loader", Console::out_stderr, log_level, logging_enabled);
  }

  if (!logging_enabled){
      zel_logger->set_level(spdlog::level::off);
  }
  
  return zel_logger;
}

} // namespace loader

#endif