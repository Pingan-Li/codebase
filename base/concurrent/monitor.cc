#include "base/concurrent/monitor.h"

namespace base {
Monitor::Monitor() {
  // default attr.
  pthread_mutex_init(&mtx_, nullptr);
  pthread_cond_init(&cv_, nullptr);
}

// TODO: Wrong impl.
void Monitor::Wait() {
  pthread_mutex_lock(&mtx_);
  pthread_cond_wait(&cv_, &mtx_);
}

void Monitor::NotifyAll() { pthread_cond_signal(&cv_); }

void Monitor::NotifyOne() { pthread_cond_broadcast(&cv_); }

Monitor::~Monitor() {
  pthread_cond_destroy(&cv_);
  pthread_mutex_destroy(&mtx_);
}
} // namespace base