/**
 * @file mutex.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef BASE_CONCURRENT_MUTEX_H_
#define BASE_CONCURRENT_MUTEX_H_

#include <pthread.h>

#include "base/macro.h"

namespace base {
class API Mutex final {
public:
  Mutex();
  // Once a mutex is created, it cannot be validly copied or moved to a new
  // location.
  DISABLE_COPY(Mutex);
  DISABLE_MOVE(Mutex);

  // Acquire the ownership of this mutex.
  void Acquire();
  // Release the ownership of this mutex.
  void Release();

  // Not virtual as base::Mutex is final.
  ~Mutex();

private:
  pthread_mutex_t pm_;
};
} // namespace base
#endif