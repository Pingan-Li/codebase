/**
 * @file vector.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_ALGORITHM_VECTOR_H_
#define BASE_ALGORITHM_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <limits>
#include <utility>

#include "base/allocator/simple_allocator.h"
#include "base/container/internal/pointer_iterator.h"

namespace base {
template <typename T, typename Allocator = SimpleAllocator<T>>
class Vector final {
public:
  using Iter = iterator<T, Vector>;
  using ConstIter = const_iterator<T, Vector>;
  using ReverseIter = reverse_iterator<T, Vector>;
  using ConstReverseIter = const_reverse_iterator<T, Vector>;

  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  Vector(std::size_t n) : data_(nullptr), size_(0), capacity_(n) {
    data_ = allocator_.allocate(n);
  }
  // final
  ~Vector() { allocator_.deallocate(data_); }

  // Iterators.
  Iter begin() { return Iter{data_}; }
  Iter end() { return Iter{data_ + size_}; }
  ReverseIter rbegin() { return ReverseIter{data_ + size_ - 1}; }
  ReverseIter rend() { return ReverseIter{data_ - 1}; }
  ConstIter cbegin() const { return ConstIter{data_}; }
  ConstIter cend() const { return ConstIter{data_ + size_}; }
  ConstReverseIter crbegin() const {
    return ConstReverseIter{data_ + size_ - 1};
  }
  ConstReverseIter crend() const { return ConstReverseIter{data_ - 1}; }
  // ~Iterators.

  // Element Access
  T &At(std::size_t index) { return data_[index]; }
  T const &At(std::size_t index) const { return data_[index]; }
  T &operator[](std::size_t index) { return data_[index]; }
  T const &operator[](std::size_t index) const { return data_[index]; }
  T &Front() { return data_[0]; }
  T const &Front() const { return data_[0]; }
  T &Back() { return data_[size_ - 1]; }
  T const &Back() const { return data_[size_ - 1]; }
  T *Data() noexcept { return data_; }
  T const *Data() const noexcept { return data_; }
  // ~Element Access
  // Size
  bool Empty() const noexcept { return size_ == 0; }
  std::size_t Size() const noexcept { return size_; }
  std::size_t MaxSize() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
  std::size_t Capacity() const noexcept { return capacity_; }
  void ShrinkToFit() const {}
  // ~Size
  // Modifiers
  void Clear() {}
  void Insert() {}
  void Emplace(T &&t) {}
  Iter Erase() {}
  void PushBack(T const &t) {
    EnsureCapacity();
    data_[size_++] = t;
  }

  void PushBack(T &&t) {
    EnsureCapacity();
    data_[size_++] = std::move(t);
  }

  T PopBack() { return std::move(data_[--size_]); }
  // ~Modifiers

  void Reserve(std::size_t n) {}
  void Resize(std::size_t n, T const &t) {
    capacity_ = n;
    size_ = n;
    T *new_area = allocator_.allocate(n);
  }

private:
  // internal funcitons.
  friend class VectorTestHelper;
  void EnsureCapacity() {
    if (!data_) {
      capacity_ = 4u;
      data_ = allocator_.allocate(capacity_);
      return;
    }
    if (size_ == capacity_) {
      capacity_ <<= 1;
      T *new_data = allocator_.allocate(capacity_);
      for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
      allocator_.deallocate(data_);
      data_ = new_data;
    }
  }

  // data members.
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  Allocator allocator_{};
};
} // namespace base
#endif