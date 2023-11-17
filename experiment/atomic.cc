/**
 * @file atomic.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "testing/googletest/include/gtest/gtest.h"
#include <atomic>
#include <thread>

constexpr int count = 1000000;

int volatile value = 0;
void Accumulate(int volatile *value) {
  for (int i = 0; i < count; ++i) {
    *value = *value + 1;
  }
}

TEST(Volatile, Accumulate) {
  std::thread t1(Accumulate, &value);
  std::thread t2(Accumulate, &value);
  t1.join();
  t2.join();
  ASSERT_EQ(value, 2 * count);
}

std::atomic_int atomic_value = 0;
void AtomicAccumulate(std::atomic_int &value) {
  for (int i = 0; i < count; ++i) {
    ++atomic_value;
  }
}

TEST(Atomic, Accumulate) {
  std::thread t1(AtomicAccumulate, std::ref(atomic_value));
  std::thread t2(AtomicAccumulate, std::ref(atomic_value));
  std::thread t3(AtomicAccumulate, std::ref(atomic_value));
  std::thread t4(AtomicAccumulate, std::ref(atomic_value));
  std::thread t5(AtomicAccumulate, std::ref(atomic_value));
  std::thread t6(AtomicAccumulate, std::ref(atomic_value));
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  ASSERT_EQ(atomic_value, 6 * count);
}
