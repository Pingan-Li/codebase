/**
 * @file semaphore.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_CONCURRENT_SEMAPHORE_H_
#define BASE_CONCURRENT_SEMAPHORE_H_

#include "base/concurrent/condition_variable.h"
#include "base/concurrent/mutex.h"
#include "base/macro.h"

namespace base {
class API Semaphore final {
public:
  Semaphore();
  Semaphore(int count);

  DISABLE_COPY(Semaphore);
  DISABLE_MOVE(Semaphore);

  ~Semaphore();

  void Wait();

  void Signal();

private:
  int count_;
  Mutex mtx_;
  ConditionVariable cv_;
};
} // namespace base
#endif