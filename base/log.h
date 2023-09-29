/**
 * @file log.h
 * @author lipingan (lipingan@hisense.com)
 * @brief
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_LOG_H_
#define BASE_LOG_H_

#include <cstddef>
#include <cstring>

#include "base/algorithm/find.h"
#include "base/timestamp.h"

#define LOG(level) base::Log(__FILE__, __LINE__, level)

namespace base {

enum LogLevel {
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL,
};

/**
 * @brief Extact the file name from macro __FILE__
 *
 */
class FileName;
class Logger;
class LoggerStream;

class FileName {
public:
  template <std::size_t N>
  explicit FileName(char const (&file_name)[N])
      : name_(file_name), size_(N - 1) {
    std::size_t index = FindBack(file_name, '/');
    if (index != -1) {
      name_ += (index + 1);
      size_ -= (index + 1);
    }
  }

  explicit FileName(char *const file_name);

  char const *name_;
  std::size_t size_;
};

class LoggerStream {
public:
  LoggerStream &operator<<(char const *message) { return *this; }
};

class Logger {
public:
  Logger(FileName file, int line);
  Logger(FileName file_name, int line, LogLevel level);
  Logger(FileName file_name, int line, LogLevel level, const char *callback);
  ~Logger();
  class LoggerImpl {

  public:
    LoggerImpl(LogLevel level, int old_errno, FileName const &file, int line);
    void formatTime();
    void finish();

    Timestamp time_;
    LoggerStream stream_;
    LogLevel level_;
    int line_;
    FileName basename_;
  };
};

LoggerStream &Log(FileName file_name, LogLevel level);
} // namespace base
#endif