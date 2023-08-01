#ifndef BASE_CONCURRENT_MONITOR_H_
#define BASE_CONCURRENT_MONITOR_H_

#include "base/macro.h"

#include <pthread.h>

namespace base {
// A monitor consists of a mutex (lock) object and condition variables.
// https://en.wikipedia.org/wiki/Monitor_(synchronization)
class API Monitor final {
public:
  Monitor();

  DISABLE_COPY(Monitor);
  DISABLE_MOVE(Monitor);

  void Wait();

  void NotifyAll();

  void NotifyOne();

  ~Monitor();

private:
  pthread_mutex_t mtx_;
  pthread_cond_t cv_;
};
} // namespace base
#endif