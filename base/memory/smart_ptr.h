/**
 * @file smart_ptr.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_SMART_PTR_H_
#define BASE_SMART_PTR_H_
#include <atomic>

namespace base {

template <typename T> struct ControllBlock {
  using CountType = std::atomic_uint32_t;
  CountType shard_count;
  CountType weak_count;
  std::atomic<T *> address;
};

// TODO
template <typename T> class ShardPtr {
public:
  explicit ShardPtr(T *pointer) : cb_(new ControllBlock<T>) {
    if (!pointer) {
      cb_->shard_count.store(0u);
      cb_->weak_count.store(0u);
      cb_->address = nullptr;
    }
  }

  template <typename... Args> explicit ShardPtr(Args &&...args) {}

  void operator->();

private:
  ControllBlock<T> *cb_;
};

} // namespace base
#endif