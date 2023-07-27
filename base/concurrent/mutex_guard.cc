#include "base/concurrent/mutex_guard.h"
#include "base/concurrent/mutex.h"

namespace base {
MutexGuard::MutexGuard(Mutex &mutex) : mutex_(mutex) { mutex_.Acquire(); }

MutexGuard::~MutexGuard() { mutex_.Release(); }
} // namespace base