#include "base/concurrent/mutex.h"
#include "base/concurrent/mutex_guard.h"
#include "base/concurrent/restrict_mutex.h"
#include <iostream>

void TestMutex() {
  base::Mutex mutex;
  base::MutexGuard<base::Mutex> mutex_guard(mutex);
}

void TestRestrictMutex() {
  base::RestrictMutex mutex;
  base::MutexGuard<base::RestrictMutex> mutex_guard(mutex);
}

int main(int argc, char **argv) {
  TestMutex();
  TestRestrictMutex();
}