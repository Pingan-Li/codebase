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
#include "base/container/internal/iterator.h"
#include "base/container/internal/pointer_iterator.h"

namespace base {
template <typename T, typename Allocator = SimpleAllocator<T>>
class Vector final {
public:
  using iterator = PointerIterator<T, Vector>;
  using const_iterator = PointerIterator<T const, Vector>;
  using reverse_iteraotr = ReverseIterator<iterator>;
  using const_reverse_iterator = ReverseIterator<const_iterator>;

  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  Vector(std::size_t n) : data_(nullptr), size_(0), capacity_(n) {
    data_ = allocator_.allocate(n);
  }
  // final
  ~Vector() { allocator_.deallocate(data_); }

  // Iterators.
  iterator begin() { return iterator(data_); }
  iterator end() { return iterator(data_ + size_); }

  reverse_iteraotr rbegin() { return reverse_iteraotr(end()); }
  reverse_iteraotr rend() { return reverse_iteraotr(begin()); }

  const_iterator cbegin() const { return const_iterator(data_); }
  const_iterator cend() const { return const_iterator(data_ + size_); }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin());
  }
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
  void Clear() {
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i].~T();
    }
    size_ = 0;
  }
  void Insert(const_iterator const_iter) {}
  void Emplace(T &&t) {}
  iterator Erase() {}
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