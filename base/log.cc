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
namespace base {
FileName::FileName(char *const file_name) : name_(file_name) {
  size_ = strlen(file_name);
  std::size_t index = FindBack(name_, size_, '/');
  if (index != -1) {
    name_ += (index + 1);
    size_ -= (index + 1);
  }
}
} // namespace base