/**
 * @file store_load_reordering_exp.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>

int x = 0;
int y = 0;

int a = 0;
int b = 0;

std::atomic_int i;
std::atomic_int j;

std::atomic_flag flag0{false};
std::atomic_flag flag1{false};

void Func0() {
  while (true) {
    if (!flag0.test(std::memory_order_acquire)) {
      x = 1;
      // __asm__ __volatile__("dmb sy");
      a = y;
      flag0.test_and_set(std::memory_order_release);
      i.fetch_add(1, std::memory_order_release);
    }
  }
}

void Func1() {
  while (true) {
    if (!flag1.test(std::memory_order_acquire)) {
      y = 1;
      // __asm__ __volatile__("dmb sy");
      b = x;
      flag1.test_and_set(std::memory_order_release);
      j.fetch_add(1, std::memory_order_release);
    }
  }
}

int main() {
  std::thread thread0{Func0};
  std::thread thread1{Func1};
  int iterations = 0;
  int reordering = 0;
  while (true) {
    if (flag0.test(std::memory_order_acquire) &&
        flag1.test(std::memory_order_acquire)) {
      ++iterations;
      if (a == 0 && b == 0) {
        ++reordering;
      }
      a = 0;
      b = 0;
      x = 0;
      y = 0;
      flag0.clear(std::memory_order_release);
      flag1.clear(std::memory_order_release);
      std::cout << "Reordering ratio = "
                << reordering / static_cast<double>(iterations) * 100
                << " %\n ";
      assert(i == j);
    }
  }

  thread0.join();
  thread1.join();
}