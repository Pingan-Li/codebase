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

namespace base {
class Logger {
public:
  enum LogLevel {
    ALL,
    TRACE,
    DEBUG,
    WARN,
    INFO,
    ERROR,
    FATAL,
    OFF,
  };

  void Log(char const *message, std::size_t length);
};

class LoggerStream {
public:
  LoggerStream &operator<<(char const *message) { return *this; }
};
} // namespace base
#endif