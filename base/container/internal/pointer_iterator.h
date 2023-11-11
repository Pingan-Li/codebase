/**
 * @file pointer_iterator.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_CONTAINER_INTERNAL_POINTER_ITERATOR_H_
#define BASE_CONTAINER_INTERNAL_POINTER_ITERATOR_H_

#include "base/container/internal/iterator_traits.h"
#include <cstddef>

namespace base {

/**
 * @brief A iterator to wrap pointer.
 *
 */
template <typename T, typename Container> class PointerIterator {
public:
  using P = T *;
  using IteratorCategory = typename IteratorTraits<P>::IteratorCategory;
  using value_type = typename IteratorTraits<P>::IteratorCategory;
  using pointer = typename IteratorTraits<P>::pointer;
  using reference = typename IteratorTraits<P>::reference;
  using difference_type = typename IteratorTraits<P>::difference_type;

  PointerIterator() noexcept = default;
  PointerIterator(T *p) noexcept : p_(p) {}

  // `const` is needed, becauese the constancy of iterator has
  // noting to do with T.
  reference operator*() const noexcept { return *p_; }

  pointer operator->() const noexcept { return p_; }

  PointerIterator &operator++() noexcept {
    ++p_;
    return *this;
  }

  PointerIterator &operator--() noexcept {
    --p_;
    return *this;
  }

  PointerIterator operator++(int) noexcept {
    auto tmp = p_;
    ++p_;
    return PointerIterator(p_);
  }

  PointerIterator operator--(int) noexcept {
    auto tmp = p_;
    --p_;
    return PointerIterator(p_);
  }

  PointerIterator &operator+=(difference_type diff) noexcept {
    p_ += diff;
    return *this;
  }

  PointerIterator &operator-=(difference_type diff) noexcept {
    p_ -= diff;
    return *this;
  }

  PointerIterator operator+(difference_type diff) const noexcept {
    return PointerIterator{p_ + diff};
  }

  PointerIterator operator-(difference_type diff) const noexcept {
    return PointerIterator{p_ - diff};
  }

  bool operator==(PointerIterator const &other) const noexcept {
    return p_ == other.p_;
  }

  bool operator!=(PointerIterator const &other) const noexcept {
    return !(*this == other);
  }

  reference operator[](difference_type diff) const noexcept { return p_[diff]; }

private:
  pointer p_ = nullptr;
};

/**
 * @brief constant iterator.
 *
 */
template <typename T, typename Container> class const_iterator {
public:
  using difference_type = std::ptrdiff_t;
  const_iterator() noexcept = default;
  const_iterator(T *p) noexcept : p_(p) {}
  const_iterator(T const *p) noexcept : p_(p) {}

  T const &operator*() const noexcept { return *p_; }

  T const *operator->() const noexcept { return p_; }

  const_iterator &operator++() noexcept {
    ++p_;
    return *this;
  }

  const_iterator &operator--() noexcept {
    --p_;
    return *this;
  }

  const_iterator operator++(int) noexcept { return const_iterator(p_++); }

  const_iterator operator--(int) noexcept { return const_iterator(p_--); }

  const_iterator &operator+=(difference_type diff) noexcept {
    p_ += diff;
    return *this;
  }

  const_iterator &operator-=(difference_type diff) noexcept {
    p_ -= diff;
    return *this;
  }

  const_iterator operator+(difference_type diff) const noexcept {
    return const_iterator{p_ + diff};
  }

  const_iterator operator-(difference_type diff) const noexcept {
    return const_iterator{p_ - diff};
  }

  T const &operator[](difference_type diff) const noexcept { return p_[diff]; }

private:
  T const *p_{};
};

/**
 * @brief
 *
 * @tparam T - Data type
 * @tparam Container - Container is used to distinguish iterator types
 */
template <typename T, typename Container> class reverse_iterator {
public:
  using difference_type = std::ptrdiff_t;
  using BaseIterator = PointerIterator<T, Container>;

  reverse_iterator() noexcept = default;
  reverse_iterator(T *p) noexcept : p_(p) {}

  T &operator*() const noexcept { return *p_; }

  T *operator->() const noexcept { return p_; }

  reverse_iterator &operator++() noexcept {
    --p_;
    return *this;
  }

  reverse_iterator &operator--() noexcept {
    ++p_;
    return *this;
  }

  reverse_iterator operator++(int) noexcept { return reverse_iterator(p_--); }

  reverse_iterator operator--(int) noexcept { return reverse_iterator(p_++); }

  reverse_iterator &operator+=(difference_type diff) noexcept {
    p_ -= diff;
    return *this;
  }

  reverse_iterator &operator-=(difference_type diff) noexcept {
    p_ += diff;
    return *this;
  }

  reverse_iterator operator+(difference_type diff) const noexcept {
    return reverse_iterator{p_ - diff};
  }

  reverse_iterator operator-(difference_type diff) const noexcept {
    return reverse_iterator{p_ + diff};
  }

  T &operator[](difference_type diff) const noexcept { return p_[-diff]; }

  BaseIterator base() const { return BaseIterator{p_ + 1}; }

private:
  T *p_{};
};

template <typename T, typename Container> class const_reverse_iterator {
public:
  using difference_type = std::ptrdiff_t;
  using BaseIterator = const_iterator<T, Container>;

  const_reverse_iterator() noexcept = default;
  const_reverse_iterator(T *p) noexcept : p_(p) {}

  T const &operator*() const noexcept { return *p_; }

  T const *operator->() const noexcept { return p_; }

  const_reverse_iterator &operator++() noexcept {
    --p_;
    return *this;
  }

  const_reverse_iterator &operator--() noexcept {
    ++p_;
    return *this;
  }

  const_reverse_iterator operator++(int) noexcept {
    return const_reverse_iterator(p_--);
  }

  const_reverse_iterator operator--(int) noexcept {
    return const_reverse_iterator(p_++);
  }

  const_reverse_iterator &operator+=(difference_type diff) noexcept {
    p_ -= diff;
    return *this;
  }

  const_reverse_iterator &operator-=(difference_type diff) noexcept {
    p_ += diff;
    return *this;
  }

  const_reverse_iterator operator+(difference_type diff) const noexcept {
    return const_reverse_iterator{p_ - diff};
  }

  const_reverse_iterator operator-(difference_type diff) const noexcept {
    return const_reverse_iterator{p_ + diff};
  }

  T &operator[](difference_type diff) const noexcept { return p_[-diff]; }

  BaseIterator base() const { return BaseIterator{p_ + 1}; }

private:
  T *const p_{};
};

template <typename T, typename Container>
bool operator==(PointerIterator<T, Container> const &lhs,
                PointerIterator<T, Container> const &rhs) {
  return lhs.p_ == rhs.p_;
}

template <typename T, typename Container>
bool operator!=(PointerIterator<T, Container> const &lhs,
                PointerIterator<T, Container> const &rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator==(const_iterator<T, Container> const &lhs,
                const_iterator<T, Container> const &rhs) {
  return lhs.p_ == rhs.p_;
}

template <typename T, typename Container>
bool operator!=(const_iterator<T, Container> const &lhs,
                const_iterator<T, Container> const &rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator==(reverse_iterator<T, Container> const &lhs,
                reverse_iterator<T, Container> const &rhs) {
  return lhs.p_ == rhs.p_;
}

template <typename T, typename Container>
bool operator!=(reverse_iterator<T, Container> const &lhs,
                reverse_iterator<T, Container> const &rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator==(const_reverse_iterator<T, Container> const &lhs,
                const_reverse_iterator<T, Container> const &rhs) {
  return lhs.p_ == rhs.p_;
}

template <typename T, typename Container>
bool operator!=(const_reverse_iterator<T, Container> const &lhs,
                const_reverse_iterator<T, Container> const &rhs) {
  return !(lhs == rhs);
}

} // namespace base
#endif