/**
 * @file adaptive_lock.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "base/concurrent/lock/adaptive_lock.h"
#include <atomic>
#include <thread>

namespace base {
AdaptiveLock::AdaptiveLock(int spin_limit, int pause_limit) noexcept
    : spin_limit_(spin_limit), pause_limit_(pause_limit) {}

// TODO
void AdaptiveLock::Lock() noexcept {
  while (is_locked_.exchange(true, std::memory_order_acq_rel)) {
    std::this_thread::yield();
  }
}

bool AdaptiveLock::TryLock() noexcept {
  bool slot = false;
  return is_locked_.compare_exchange_strong(slot, true,
                                            std::memory_order_acq_rel);
}

void AdaptiveLock::UnLock() noexcept {
  is_locked_.store(false, std::memory_order_release);
}
}  // namespace base