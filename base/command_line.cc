/**
 * @file command_line.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/command_line.h"

#include <mutex>

namespace base {

static CommandLine *g_instance;

CommandLine::CommandLine() = default;

CommandLine::~CommandLine() = default;

// static
void CommandLine::Initialize(int argc, char *argv[]) {
  static std::once_flag flag;
  std::call_once(flag, [argc, argv]() noexcept -> void {
    g_instance = new CommandLine;
    for (int i = 0; i < argc; ++i) {
    }
  });
}

// static
CommandLine *CommandLine::Get() noexcept { return nullptr; }

} // namespace base