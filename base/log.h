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
#include <sstream>

#include "base/algorithm/find.h"
#include "base/timestamp.h"

// [pid, tid, data, time, level, filename, line] LogMessage

namespace base {

namespace log {

class LogConfiguration final {
public:
  constexpr LogConfiguration() = default;

  ~LogConfiguration() = default;

  void SetUseNanoseconds(bool flag) noexcept;

  bool GetUseNanoseconds() const noexcept;

private:
  bool use_nanoseconds{false};
};

void Initialize(LogConfiguration const &logging_configuration);

enum LogSeverity { DEBUG, INFO, WARNING, ERROR, FATAL };

class LogMessage final {
public:
  LogMessage(char const *file_name, int code_line,
             LogSeverity severity) noexcept;

  ~LogMessage();

  std::ostream &Stream() noexcept;

  std::string ToString() noexcept;

private:
  char const *file_name_{nullptr};
  int code_line_{0};
  LogSeverity severity_;
  std::ostringstream stream_;
};

} // namespace log

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
    if (index != 1U) {
      name_ += (index + 1);
      size_ -= (index + 1);
    }
  }

  explicit FileName(char *const file_name);

  char const *name_;
  std::size_t size_;
};

#define COMPACT_LOG_EX_DEBUG(ClassName, ...)                                   \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LogLevel::DEBUG,         \
                       ##__VA__ARGS__)
#define COMPACT_LOG_EX_INFO(ClassName, ...)                                    \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LogLevel::INFO,          \
                       ##__VA__ARGS__)
#define COMPACT_LOG_EX_WARNING(ClassName, ...)                                 \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LogLevel::WARNING,       \
                       ##__VA__ARGS__)
#define COMPACT_LOG_EX_ERROR(ClassName, ...)                                   \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LogLevel::ERROR,         \
                       ##__VA__ARGS__)
#define COMPACT_LOG_EX_FATAL(ClassName, ...)                                   \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LogLevel::FATAL,         \
                       ##__VA__ARGS__)

#define COMPACT_LOG_DEBUG COMPACT_LOG_EX_DEBUG(LogMessage)
#define COMPACT_LOG_INFO COMPACT_LOG_EX_INFO(LogMessage)
#define COMPACT_LOG_WARNING COMPACT_LOG_EX_WARNING(LogMessage)
#define COMPACT_LOG_ERROR COMPACT_LOG_EX_ERROR(LogMessage)
#define COMPACT_LOG_FATAL COMPACT_LOG_EX_FATAL(LogMessage)

#define LOG_IS_ON(log_level)
#define LOG_STREAM(severity) COMPACT_LOG_##severity.stream();
#define LAZY_STREAM(stream, condition)                                         \
  !(condition) ? (void)0 : ::logging::LogMessageVoidify() & (stream)

#define LOG(severity) LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))
} // namespace base

#endif