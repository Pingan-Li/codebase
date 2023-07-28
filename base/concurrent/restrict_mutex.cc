#include "base/concurrent/restrict_mutex.h"
#include <pthread.h>
namespace base {
RestrictMutex::RestrictMutex() : pm_(PTHREAD_MUTEX_INITIALIZER) {
  pthread_mutex_init(&pm_, nullptr);
}

void RestrictMutex::Acquire() { pthread_mutex_lock(&pm_); }

void RestrictMutex::Release() { pthread_mutex_unlock(&pm_); }

RestrictMutex::~RestrictMutex() { pthread_mutex_destroy(&pm_); }
} // namespace base