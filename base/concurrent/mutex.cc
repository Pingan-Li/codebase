#include "base/concurrent/mutex.h"
#include <pthread.h>

namespace base {
Mutex::Mutex() : pm_(PTHREAD_MUTEX_INITIALIZER) {
  pthread_mutex_init(&pm_, nullptr);
};

void Mutex::Acquire() { pthread_mutex_lock(&pm_); }

void Mutex::Release() { pthread_mutex_unlock(&pm_); }

Mutex::~Mutex() { pthread_mutex_destroy(&pm_); };
} // namespace base