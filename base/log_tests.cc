/**
 * @file log_tests.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/log.h"

#include <cstddef>

#include "testing/googletest/include/gtest/gtest.h"

namespace base {
class LogTestHelper : public testing::Test {
public:
  void SetUp() override {}

  void TearDown() override {}
};

/**
 * @brief Taken from mudo.
 *
 */
class SourceFile {
public:
  template <int N> SourceFile(const char (&arr)[N]) : data_(arr), size_(N - 1) {
    const char *slash = strrchr(data_, '/'); // builtin function
    if (slash) {
      data_ = slash + 1;
      size_ -= static_cast<int>(data_ - arr);
    }
  }

  explicit SourceFile(const char *filename) : data_(filename) {
    const char *slash = strrchr(filename, '/');
    if (slash) {
      data_ = slash + 1;
    }
    size_ = static_cast<int>(strlen(data_));
  }
  friend class LogTestHelper;
  const char *data_;
  int size_;
};

TEST_F(LogTestHelper, case0) {
  SourceFile source_file(__FILE__);
  FileName file_name(__FILE__);
  ASSERT_STREQ(source_file.data_, file_name.name_);
  ASSERT_EQ(source_file.size_, source_file.size_);
}

TEST(LogMessage, message) {
  log::LogMessage(__FILE__, __LINE__, log::LogSeverity::ERROR);
}

} // namespace base