/**
 * @file command_line.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef BASE_COMMAND_LINE_H_
#define BASE_COMMAND_LINE_H_

#include <optional>
#include <string>
#include <vector>

#include "base/macro.h"

namespace base {
class CommandLine final {

public:
  using KeyType = std::string;
  using ValType = std::string;
  struct Argument {
    KeyType key;
    std::optional<ValType> val;
  };

  static void Initialize(int argc, char *argv[]);

  static CommandLine *Get() noexcept;

private:
  CommandLine();

  DISABLE_COPY(CommandLine);
  DISABLE_MOVE(CommandLine);

  ~CommandLine();

  std::vector<Argument> args_;
};
} // namespace base

#endif