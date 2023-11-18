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
#include <limits>
#include <memory>

#include "base/allocator/simple_allocator.h"
#include "base/container/internal/iterator.h"
#include "base/memory/lifetime.h"

namespace base {

template <typename T, typename Allocator> class VectorBase {
public:
  VectorBase() noexcept = default;
  VectorBase(Allocator const &allocator) noexcept : allocator_(allocator) {}

  using allocator_type = Allocator;
  using allocator_traits = std::allocator_traits<allocator_type>;
  using size_type = typename allocator_traits::size_type;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using difference_type = typename allocator_traits::difference_type;
  using pointer = typename allocator_traits::pointer;
  using const_pointer = typename allocator_traits::const_pointer;

  Allocator allocator_;
};

template <typename T, typename Allocator = SimpleAllocator<T>>
class Vector final : private VectorBase<T, Allocator> {
public:
  using Super = VectorBase<T, Allocator>;
  using iterator = GenericIterator<T *>;
  using const_iterator = GenericIterator<T const *>;
  using reverse_iteraotr = GenericReverseIterator<iterator>;
  using const_reverse_iterator = GenericReverseIterator<const_iterator>;
  using size_type = typename Super::allocator_traits::size_type;
  /**
   * @brief Constructor (1) Default constructor. Constructs an empty container
   * with a default-constructed allocator.
   *
   */
  Vector() noexcept(noexcept(Allocator()))
      : Super(), data_(nullptr), size_(0), capacity_(0) {}

  /**
   * @brief Constructor (2) Constructs an empty container with the given
   * allocator `allocator`.
   *
   * @param allocator
   */
  explicit Vector(Allocator const &alloc) : Super(alloc) {}

  /**
   * @brief Constructor (3) Constructs the container with n copies of
   * elements with value `value`.
   *
   * @param n
   */

  Vector(size_type n, T const &value, const Allocator &alloc = Allocator())
      : Super(), data_(this->allocator_.allocate()), size_(), capacity_(n) {
    for (size_type idx = 0; idx < size_; ++idx) {
      data_[idx] = value;
      ++size_;
    }
  }

  /**
   * @brief Constructor (4) Constructs the container with count default-inserted
   * instances of T. No copies are made.
   *
   * @param n
   */
  explicit Vector(size_type n)
      : Super(), data_(this->allocator_.allocate(n)), size_(0), capacity_(n) {
    for (size_type idx = 0; idx < n; ++idx) {
      base::Construct(data_ + idx);
      ++size_;
    }
  }

  /**
   * @brief Constructor (5) Constructs the container with the contents of the
   * range [first, last).
   *
   * @tparam InputIterator
   * @param first
   * @param last
   * @param alloc
   */

  template <class InputIterator>
  Vector(InputIterator first, InputIterator last,
         const Allocator &alloc = Allocator()) {
    while (first != last) {
      EmplaceBack(*first);
      ++first;
    }
  }

  /**
   * @brief Constructor (6) Constructs the container with the copy of the
   * contents of other.
   *
   * @param other
   */
  Vector(Vector const &other)
      : Super(), data_(this->allocator_(other.Size())), size_(0),
        capacity_(other.Size()) {
    for (size_type idx = 0; idx < other.Size(); ++idx) {
      data_[idx] = other.data_[idx];
      ++size_;
    }
  }

  /**
   * @brief Destroy the Vector object
   *
   */

  // final
  ~Vector() { this->allocator_.deallocate(data_); }

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
  T &At(size_type index) { return data_[index]; }
  T const &At(size_type index) const { return data_[index]; }
  T &operator[](size_type index) { return data_[index]; }
  T const &operator[](size_type index) const { return data_[index]; }
  T &Front() { return data_[0]; }
  T const &Front() const { return data_[0]; }
  T &Back() { return data_[size_ - 1]; }
  T const &Back() const { return data_[size_ - 1]; }
  T *Data() noexcept { return data_; }
  T const *Data() const noexcept { return data_; }
  // ~Element Access
  // Size
  bool Empty() const noexcept { return size_ == 0; }
  size_type Size() const noexcept { return size_; }
  size_type MaxSize() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }
  size_type Capacity() const noexcept { return capacity_; }
  void ShrinkToFit() const {}
  // ~Size
  // Modifiers
  void Clear() {
    while (size_ != 0) {
      base::Destruct(data_ + --size_);
    }
  }

  iterator Insert(const_iterator const_iter, T const &t) {}

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

  template <typename... Args> void EmplaceBack(Args &&...args) {
    EnsureCapacity();
    ++size_;
    base::Construct(data_ + size_, std::forward<Args>(args)...);
  }

  T PopBack() { return std::move(data_[--size_]); }
  // ~Modifiers

  void Reserve(size_type n) {}
  void Resize(size_type n, T const &t) {
    capacity_ = n;
    size_ = n;
    T *new_area = this->allocator_.allocate(n);
  }

private:
  // internal funcitons.
  friend class VectorTestHelper;
  void EnsureCapacity() {
    if (!data_) {
      capacity_ = 4u;
      data_ = this->allocator_.allocate(capacity_);
      return;
    }
    if (size_ == capacity_) {
      capacity_ <<= 1;
      T *new_data = this->allocator_.allocate(capacity_);
      for (size_type i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
      this->allocator_.deallocate(data_);
      data_ = new_data;
    }
  }

  // data members.
  T *data_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;
};
} // namespace base
#endif