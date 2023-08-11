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

#include <map>
#include <optional>
#include <string>

#include "base/macro.h"

namespace base {
/**
 * @brief commanline argument parser.
 *        support:
 *          (1) --key
 *          (2) --key=val
 *          (3) -k,
 *          (4) -k=val
 *
 */

class API CommandLine final {
public:
  using Key = std::string;
  using Val = std::string;

  static void Initialize(int argc, char *argv[]);

  static CommandLine *Get() noexcept;

  bool HasKey(Key const &key) const;

  std::optional<Val> GetVal(Key const &key) const;

private:
  CommandLine();

  DISABLE_COPY(CommandLine);
  DISABLE_MOVE(CommandLine);

  ~CommandLine();

  std::map<Key, std::optional<Val>> args_;
};
} // namespace base

#endif