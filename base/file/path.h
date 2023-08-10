/**
 * @file path.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef BASE_FILE_PATH_H_
#define BASE_FILE_PATH_H_

#include <string>

namespace base {
class Path {
public:
  Path(std::string const &raw_path);

  Path(Path const &other);
  Path &operator=(Path const &other);
  Path(Path &&other);
  Path &operator=(Path &&other);

  void Append(std::string const &sub_path);

  void Append(Path const &sub_path);

  virtual ~Path();
};
} // namespace base

#endif