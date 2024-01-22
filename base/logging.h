/**
 * @file logging.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_LOGGING_H_
#define BASE_LOGGING_H_

#include <cstddef>
#include <string>

namespace base {

#define LOG(level) ;

class OnceMessage {
public:
  OnceMessage(char const *file, char const);
};

class LoggerStream {
public:
  LoggerStream &operator<<(char) { return *this; }
  LoggerStream &operator<<(char unsigned) { return *this; }
  LoggerStream &operator<<(char signed) { return *this; }

  LoggerStream &operator<<(int) { return *this; }
  LoggerStream &operator<<(int unsigned) { return *this; }

  LoggerStream &operator<<(int short) { return *this; }
  LoggerStream &operator<<(int unsigned short) { return *this; }

  LoggerStream &operator<<(int long) { return *this; }
  LoggerStream &operator<<(int unsigned long) { return *this; }

  LoggerStream &operator<<(int long long) { return *this; }
  LoggerStream &operator<<(int unsigned long long) { return *this; }
};

class Logger {
public:
  struct Configuration {
    std::string logging_file_name;
    std::size_t logging_file_size = 1024U * 1024U * 1024U;
  };

  enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
  };

  static void Initialize(Configuration const &configuration);
  static Logger *Get() noexcept;

  inline LoggerStream &Stream() noexcept { return logger_stream_; }

private:
  Logger(Configuration const &configuration);

  LoggerStream logger_stream_;
};

} // namespace base
#endif