/**
 * @file thread_local.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "testing/googletest/include/gtest/gtest.h"

thread_local int i = 0;
void Func(int count) {
  for (int j = 0; j < count; ++j) {
    ++i;
  }
  std::printf("ThreadID = %u, i = %d\n", std::this_thread::get_id(), count);
}

TEST(ThreadLocal, Heck) {
  std::thread thread0(Func, 300);
  std::thread thread1(Func, 500);

  thread0.join();
  thread1.join();
}