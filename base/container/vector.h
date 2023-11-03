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
#include "base/allocator/simple_allocator.h"
#include <cstddef>
namespace base {
template <typename T, typename Allocator = SimpleAllocator<T>>
class Vector final {
public:
  Vector() : data_(nullptr), size_(0), capacity_(0) {}
  Vector(std::size_t n) : data_(nullptr), size_(0), capacity_(n) {
    data_ = allocator_.allocate(n);
  }
  ~Vector() { allocator_.deallocate(data_); }

  // STL style operations.
  using iterator = T *;
  using const_iterator = T const *;
  iterator begin();
  iterator end();
  iterator rbegin();
  iterator rend();
  const_iterator cbegin() const;
  const_iterator cend() const;
  const_iterator crbegin() const;
  const_iterator crend() const;
  // ~STL style operations.

  // operaitons.
  void PushBack(T const &t);
  void PushBack(T &&t);

  T PopBack();

  T &Head();
  T &Tail();
  T const &Head() const;
  T const &Tail() const;

  T &At(std::size_t index) { return data_[index]; }
  T const &At(std::size_t index) const { return data_[index]; }

  void Reserve(std::size_t n) {}
  void Resize(std::size_t n, T const &t) {
    capacity_ = n;
    size_ = n;
    T *new_area = allocator_.allocate(n);
  }

  // operators overloading.
  T &operator[](std::size_t index) { return data_[index]; }
  T const &operator[](std::size_t index) const { return data_[index]; }

private:
  // internal funcitons.
  void Expand() {
    capacity_ <<= 1;
    T *new_area = allocator_.allocate(capacity_);
    for (std::size_t i = 0; i < size_; ++i) {
      new_area[i] = std::move(data_[i]);
    }
    allocator_.deallocate(data_);
    data_ = new_area;
  }

  // data members.
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  Allocator allocator_{};
};
} // namespace base
#endif