/**
 * @file thread_printing.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <condition_variable>
#include <iostream>
#include <mutex>

namespace a {
std::mutex mtx;
std::condition_variable cv;
int counter = 0;
inline constexpr int kMax = 30;
void print_a() {
  while (true) {
    {
      std::lock_guard<std::mutex> lock_guard{mtx};
      if (!(counter < kMax))
        break;
      if (counter % 4 == 0) {
        std::cout << "thread 0, print: A\n";
        ++counter;
      }
    }
    // notify_one() is enough.
    cv.notify_one();
  }
}

void print_b() {
  while (true) {
    std::unique_lock<std::mutex> unique_lock{mtx};
    if (!(counter < kMax))
      break;
    while (!(counter % 4 == 1)) {
      cv.wait(unique_lock);
    }
    std::cout << "thread 1, print: B\n";
    ++counter;
    unique_lock.unlock();
    // notify_one() is enough.
    cv.notify_one();
  }
}

void print_c() {
  while (true) {
    std::unique_lock<std::mutex> unique_lock{mtx};
    if (!(counter < kMax))
      break;
    while (!(counter % 4 == 2)) {
      cv.wait(unique_lock);
    }
    std::cout << "thread 2, print: C\n";
    ++counter;
    unique_lock.unlock();
    cv.notify_one();
  }
}

void print_d() {
  while (true) {
    std::unique_lock<std::mutex> unique_lock{mtx};
    if (!(counter < kMax))
      break;
    while (!(counter % 4 == 3)) {
      cv.wait(unique_lock);
    }
    std::cout << "thread 3, print: D\n";
    ++counter;
    unique_lock.unlock();
    cv.notify_one();
  }
}

void a() {
  std::thread thread0{print_a};
  std::thread thread1{print_b};
  std::thread thread2{print_c};
  std::thread thread3{print_d};

  thread0.join();
  thread1.join();
  thread2.join();
  thread3.join();
}
} // namespace a

int main(int argc, char **argv) {
  a::a();
  return 0;
}