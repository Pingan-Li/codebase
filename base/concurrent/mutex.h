#ifndef BASE_CONCURRENT_MUTEX_H_
#define BASE_CONCURRENT_MUTEX_H_

#include "base/macro.h"
#include <pthread.h>

namespace base {
class API Mutex final {
public:
  Mutex();

  DISABLE_COPY(Mutex);
  DISABLE_MOVE(Mutex);

  void Acquire();

  void Release();

  ~Mutex();

private:
  pthread_mutex_t pm_;
};
} // namespace base
#endif