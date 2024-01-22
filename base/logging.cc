/**
 * @file logging.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "base/logging.h"

#include <mutex>

namespace base {

static Logger *g_instance = nullptr;

// static
void Logger::Initialize(Configuration const &configuration) {
  static std::once_flag flag;
  std::call_once(flag, [&configuration]() -> void {
    g_instance = new Logger(configuration);
  });
}

Logger *Logger::Get() noexcept { return g_instance; }

} // namespace base