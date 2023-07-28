#ifndef BASE_CONCURRENT_RESTRICT_MUTEX_H_
#define BASE_CONCURRENT_RESTRICT_MUTEX_H_

#include "base/concurrent/mutex_guard.h"
#include "base/macro.h"
namespace base {
// Restrict mutex has private Acquire and Release.
// Must be used with base::MutextGuard<RestrictMutex>.
class API RestrictMutex final {
public:
  RestrictMutex();

  DISABLE_COPY(RestrictMutex);
  DISABLE_MOVE(RestrictMutex);

  ~RestrictMutex();

private:
  friend MutexGuard<RestrictMutex>;
  void Acquire();

  void Release();

  pthread_mutex_t pm_;
};
} // namespace base
#endif