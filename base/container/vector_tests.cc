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

TEST_F(VectorTestHelper, Iterator) {
  base::Vector<int> result;
  std::vector<int> expect;
  int array[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < sizeof(array); ++i) {
    result.PushBack(i);
    expect.push_back(i);
  }
  auto iter1 = result.begin();
  auto iter2 = expect.begin();
  for (int i = 0; i < sizeof(array); ++i) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }

  ASSERT_LT(expect.begin(), expect.end());
  ASSERT_LT(expect.cbegin(), expect.cend());
  ASSERT_LT(expect.rbegin(), expect.rend());
  ASSERT_LT(expect.crbegin(), expect.crend());

  ASSERT_LT(result.begin(), result.end());
  ASSERT_LT(result.cbegin(), result.cend());
  ASSERT_LT(result.rbegin(), result.rend());
  ASSERT_LT(result.crbegin(), result.crend());

  ASSERT_GT(expect.end(), expect.begin());
  ASSERT_GT(expect.cend(), expect.cbegin());
  ASSERT_GT(expect.rend(), expect.rbegin());
  ASSERT_GT(expect.crend(), expect.crbegin());

  ASSERT_GT(result.end(), result.begin());
  ASSERT_GT(result.cend(), result.cbegin());
  ASSERT_GT(result.rend(), result.rbegin());
  ASSERT_GT(result.crend(), result.crbegin());

  ASSERT_EQ((result.begin() - result.end()), (expect.begin() - expect.end()));
  ASSERT_EQ((result.cbegin() - result.cend()),
            (expect.cbegin() - expect.cend()));
}

TEST_F(VectorTestHelper, ReverseIterator) {
  base::Vector<int> result;
  std::vector<int> expect;
  int array[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < sizeof(array); ++i) {
    result.PushBack(i);
    expect.push_back(i);
  }
  auto iter1 = result.rbegin();
  auto iter2 = expect.rbegin();
  for (int i = 0; i < sizeof(array); ++i) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }

  ASSERT_EQ(iter1, result.rend());
  ASSERT_EQ(iter2, expect.rend());
}