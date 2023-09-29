#include "base/algorithm/find.h"
#include "testing/googletest/include/gtest/gtest.h"

namespace base {
TEST(Find, case0) {
  std::size_t index = base::Find("abc", 'c');
  ASSERT_EQ(index, 2);
}

TEST(Find, case1) {
  std::size_t index = base::Find("abc", 'a');
  ASSERT_EQ(index, 0);
}

TEST(Find, case2) {
  std::size_t index = base::Find("abc", 'z');
  ASSERT_EQ(index, -1);
}

TEST(FindBack, case0) {
  std::size_t index = base::FindBack("const T (&array)[N]", 'T');
  ASSERT_EQ(index, 6);
}

TEST(FindBack, case1) {
  std::size_t index = base::FindBack("const T (&array)[N]", 'c');
  ASSERT_EQ(index, 0);
}

TEST(FindBack, case2) {
  std::size_t index = base::FindBack("const T (&array)[N]", 'z');
  ASSERT_EQ(index, -1);
}
} // namespace base