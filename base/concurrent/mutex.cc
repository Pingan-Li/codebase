/**
 * @file mutex.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/concurrent/mutex.h"

namespace base {
Mutex::Mutex() : pm_() {
  // Using default mutex attribute.
  pthread_mutex_init(&pm_, nullptr);
};

void Mutex::Acquire() { pthread_mutex_lock(&pm_); }

void Mutex::Release() { pthread_mutex_unlock(&pm_); }

Mutex::~Mutex() { pthread_mutex_destroy(&pm_); };
} // namespace base