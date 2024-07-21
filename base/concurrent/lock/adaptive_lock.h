/**
 * @file adaptive_lock.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_CONCURRENT_ADAPTIVE_LOCK_H_
#define BASE_CONCURRENT_ADAPTIVE_LOCK_H_

#include "base/base_exports.h"

#include <atomic>

namespace base {
class BASE_EXPORT AdaptiveLock final {
 public:
  AdaptiveLock(int spin_limit = 4096, int pause_limit = 128) noexcept;

  AdaptiveLock(AdaptiveLock const&) = delete;
  AdaptiveLock& operator=(AdaptiveLock const&) = delete;

  AdaptiveLock(AdaptiveLock&&) = delete;
  AdaptiveLock& operator=(AdaptiveLock&&) = delete;

  ~AdaptiveLock() = default;

  void Lock() noexcept;

  bool TryLock() noexcept;

  void UnLock() noexcept;

 private:
  std::atomic<bool> is_locked_;
  int spin_limit_;
  int pause_limit_;
};
}  // namespace base

#endif  // BASE_CONCURRENT_ADAPTIVE_LOCK_H_