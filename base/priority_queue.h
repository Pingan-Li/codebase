/**
 * @file priority_queue.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_PRIORITY_QUEUE_H_
#define BASE_PRIORITY_QUEUE_H_

#include <cstddef>
#include <list>
#include <string>

namespace base {
template <typename T> class PriorityQueue {
public:
  PriorityQueue() = default;

  virtual ~PriorityQueue() = default;

  void Insert(T const &t) {
    auto iter = list_.begin();
    while (iter != list_.end() && t < *iter) {
      ++iter;
    }
    list_.insert(iter, t);
  }

  void PopMax() { list_.pop_front(); }

  T &Max() { return list_.front(); }

  T const &Max() const { return list_.front(); }

  std::size_t Size() const noexcept { return list_.size(); }

  bool Empty() const noexcept { return list_.empty(); }

private:
  std::list<T> list_;
};
} // namespace base
#endif // BASE_PRIORITY_QUEUE_H_