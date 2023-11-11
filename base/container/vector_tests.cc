/**
 * @file vector_tests.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/container/vector.h"
#include "testing/googletest/include/gtest/gtest.h"
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

class VectorTestHelper : public testing::Test {
public:
  void SetUp() override{};
  void TearDown() override{};
};

TEST_F(VectorTestHelper, InitialState) {
  base::Vector<int> vector;
  ASSERT_EQ(vector.Size(), 0);
  ASSERT_EQ(vector.Capacity(), 0);
  ASSERT_EQ(vector.Data(), nullptr);
  ASSERT_EQ(vector.begin(), vector.end());
  ASSERT_EQ(vector.cbegin(), vector.cend());
  ASSERT_EQ(vector.rbegin(), vector.rend());
  ASSERT_EQ(vector.crbegin(), vector.crend());
  ASSERT_EQ(vector.begin(), vector.rend().base());
  ASSERT_EQ(vector.cbegin(), vector.crend().base());
}

TEST_F(VectorTestHelper, Construction) {
  constexpr std::size_t array_size = 10;
  int a[array_size] = {
      0, 1, 2, 3, 4,
  };
  base::Vector<int> vec;
  for (int i = 0; i < array_size; ++i) {
    vec.PushBack(a[i]);
  }

  for (auto iter = vec.rbegin(); iter != vec.rend(); ++iter) {
    std::cout << *iter << ", ";
  }
}

TEST_F(VectorTestHelper, IteratorTratis) {
  std::cout
      << std::is_same<typename std::iterator_traits<int *>::iterator_category,
                      std::random_access_iterator_tag>::value;
}