/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef level_zero_loader_LOGGING_HPP
#define level_zero_loader_LOGGING_HPP

#define LOADER_LOG_FILE_DEFAULT "ze_loader.log"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

namespace loader {

class Logger {
public:
  Logger(std::string logger_name, std::string filename, std::string log_level) {

    try {
      _logger = spdlog::basic_logger_st(logger_name, filename);
    } catch (spdlog::spdlog_ex &exception) {
      std::cerr << "Unable to create log file: " << exception.what() << "\n";
      return;
    }

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

  ~Logger() { _logger->flush(); }

  void set_level(spdlog::level::level_enum log_level){
    _logger->set_level(log_level);
  }

  void log_trace(std::string msg) {
    if (!_logger)
      return;
    _logger->trace(msg);
  }
  void log_debug(std::string msg) {
    if (!_logger)
      return;
    _logger->debug(msg);
  }
  void log_info(std::string msg) {
    if (!_logger)
      return;
    _logger->info(msg);
  }
  void log_warning(std::string msg) {
    if (!_logger)
      return;
    _logger->warn(msg);
  }
  void log_error(std::string msg) {
    if (!_logger)
      return;
    _logger->error(msg);
  }
  void log_fatal(std::string msg) {
    if (!_logger)
      return;
    _logger->critical(msg);
  }

  std::shared_ptr<spdlog::logger> get_base_logger(){
    return _logger;
  }

bool log_to_console = true;
private:
  std::shared_ptr<spdlog::logger> _logger = nullptr;
};

} // namespace loader

#endif