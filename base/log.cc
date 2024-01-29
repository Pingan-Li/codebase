/**
 * @file log.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/log.h"

#include <cstddef>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <string_view>
#include <unistd.h>

#include "base/concurrent/platform_thread_linux.h"
#include "base/macro.h"

#if IS_WIN32 || IS_WIN64
constexpr char const kSlash = '\\';
#else
constexpr char const kSlash = '/';
#endif
namespace base {

namespace log {

void Initialize(LogConfiguration const &logging_configuration) {
  static LogConfiguration lc = logging_configuration;
}

LogMessage::LogMessage(char const *file_name, int code_line,
                       LogSeverity severity) noexcept
    : file_name_(file_name), code_line_(code_line), severity_(severity) {
  std::string_view sv(file_name);
  auto pos = sv.find_last_of(kSlash);
  if (pos != std::string_view::npos) {
    sv.remove_prefix(pos + 1);
    file_name_ = sv.data();
  }
  stream_ << '[' << getpid() << ':'
          << base::PlatformThread::Current::GetKernelHandle() << ' ';
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  tm *ptm = localtime(&ts.tv_sec);
  if (ptm) {
    stream_ << ptm->tm_year + 1900 << '-' << std::setw(2) << std::setfill('0')
            << ptm->tm_mon + 1 << '-' << std::setw(2) << std::setfill('0')
            << ptm->tm_mday << ' ' << ptm->tm_hour << ':' << std::setw(2)
            << std::setfill('0') << ptm->tm_min << ':' << std::setw(2)
            << std::setfill('0') << std::setw(2) << std::setfill('0')
            << ptm->tm_sec << "@" << file_name_ << '(' << code_line_ << ')'
            << "]";
  }
}

LogMessage::~LogMessage() {
  stream_ << "\n\0";
  std::string message = stream_.str();
  write(STDERR_FILENO, message.c_str(), message.size());
}

std::ostream &LogMessage::Stream() noexcept { return stream_; }

std::string LogMessage::ToString() noexcept { return stream_.str(); }

} // namespace log

FileName::FileName(char *const file_name) : name_(file_name) {
  size_ = strlen(file_name);
  std::size_t index = FindBack(name_, size_, '/');
  if (index != -1U) {
    name_ += (index + 1);
    size_ -= (index + 1);
  }
}

} // namespace base