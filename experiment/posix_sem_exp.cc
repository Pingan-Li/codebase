/**
 * @file sem_exp.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <semaphore.h>

#include <chrono>
#include <iostream>
#include <thread>

sem_t s0;
sem_t s1;

void func0() {
  while (true) {
    sem_wait(&s1);
    std::cout << "A" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds{1});
    sem_post(&s0);
  }
}

void func1() {
  while (true) {
    sem_wait(&s0);
    std::cout << "B" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds{1});
    sem_post(&s1);
  }
}

int main() {
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);
  std::thread thread_0{func0};
  std::thread thread_1{func1};

  thread_0.join();
  thread_1.join();
}