/**
 * @file spin_lock.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/concurrent/spin_lock.h"

namespace base {

SpinLock::SpinLock() noexcept : is_exclusive_(false) {}

void SpinLock::Acquire() noexcept {
  while (is_exclusive_.exchange(true, std::memory_order_acquire)) {
    // Spinning.
  }
}

void SpinLock::Release() noexcept {
  is_exclusive_.store(false, std::memory_order_release);
}

} // namespace base