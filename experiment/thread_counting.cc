/**
 * @file thread_counting.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

/**
 * @brief - solution a. using condition_variable
 *
 */
namespace a {
std::mutex mutex;
std::condition_variable condition_variable;

// atomic is not necessary.
int counter = 0;
inline constexpr int kMax = 100;

void print_even() {
  while (true) {
    {
      std::lock_guard<std::mutex> lock_guard{mutex};
      if (!(counter < kMax)) {
        break;
      }

      if ((counter % 2) == 0) {
        std::cout << "thread 1, counter: " << counter++ << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds{100});
      }

      condition_variable.notify_all();
    }
  }
}

void print_odd() {
  while (true) {
    {
      std::unique_lock<std::mutex> unique_lock{mutex};
      if (!(counter < kMax)) {
        break;
      }

      while ((counter % 2) == 0) {
        condition_variable.wait(unique_lock);
      }

      std::cout << "thread 2, counter: " << counter++ << std::endl;
      // std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
  }
}

void a() {
  std::cout << "Solution A" << std::endl;
  std::thread thread1{print_even};
  std::thread thread2{print_odd};
  thread1.join();
  thread2.join();
};
} // namespace a
/**
 * @brief - solution b. using semaphore.
 *
 */
namespace b {

#if __cplusplus > 202002L
std::binary_semaphore odd_flag{1};
std::binary_semaphore even_flag{1};

int counter = 0;
inline constexpr int kMax = 100;

void print_even() {
  while (true) {
    even_flag.acquire();
    if (!(counter < kMax)) {
      break;
    }

    if ((counter % 2) == 0) {
      std::cout << "thread 1, counter: " << counter++ << std::endl;
      // std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
    odd_flag.release();
  }
}

void print_odd() {
  while (true) {
    odd_flag.acquire();
    if (!(counter < kMax)) {
      break;
    }

    if ((counter % 2) != 0) {
      std::cout << "thread 2, counter: " << counter++ << std::endl;
      // std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
    even_flag.release();
  }
}
#endif

void b() {
#if __cplusplus > 202002L
  std::cout << "Solution B" << std::endl;
  std::thread thread1{print_even};
  std::thread thread2{print_odd};
  thread1.join();
  thread2.join();
#else
#endif
};
} // namespace b

int main(int argc, char **argv) {
  a::a();
  b::b();
  return 0;
}