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

#include <cstddef>

namespace base {

/**
 * @brief regular iterator.
 *
 */
template <typename T, typename Container> class iterator {
public:
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  iterator() noexcept = default;
  iterator(T *p) noexcept : p_(p) {}

  // `const` is needed, becauese the constancy of iterator has
  // noting to do with T.
  T &operator*() const noexcept { return *p_; }

  T *operator->() const noexcept { return p_; }

  iterator &operator++() noexcept {
    ++p_;
    return *this;
  }

  iterator &operator--() noexcept {
    --p_;
    return *this;
  }

  iterator operator++(int) noexcept { return iterator(p_++); }

  iterator operator--(int) noexcept { return iterator(p_--); }

  iterator &operator+=(difference_type diff) noexcept {
    p_ += diff;
    return *this;
  }

  iterator &operator-=(difference_type diff) noexcept {
    p_ -= diff;
    return *this;
  }

  iterator operator+(difference_type diff) const noexcept {
    return iterator{p_ + diff};
  }

  iterator operator-(difference_type diff) const noexcept {
    return iterator{p_ - diff};
  }

  bool operator==(iterator const &other) const noexcept {
    return p_ == other.p_;
  }

  bool operator!=(iterator const &other) const noexcept {
    return !(*this == other);
  }

  T &operator[](difference_type diff) const noexcept { return p_[diff]; }

private:
  T *p_{};
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
  using BaseIterator = iterator<T, Container>;

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
bool operator==(iterator<T, Container> const &lhs,
                iterator<T, Container> const &rhs) {
  return lhs.p_ == rhs.p_;
}

template <typename T, typename Container>
bool operator!=(iterator<T, Container> const &lhs,
                iterator<T, Container> const &rhs) {
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