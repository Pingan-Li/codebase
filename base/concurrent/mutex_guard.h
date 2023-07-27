#ifndef BASE_CONCURRENT_MUTEX_GUARD_H_
#define BASE_CONCURRENT_MUTEX_GUARD_H_

#include "base/concurrent/mutex.h"
#include "base/macro.h"

namespace base {
class API MutexGuard final {
public:
  explicit MutexGuard(Mutex &mutex);

  DISABLE_COPY(MutexGuard);
  DISABLE_MOVE(MutexGuard);

  ~MutexGuard();

private:
  Mutex &mutex_;
};
} // namespace base
#endif