/**
 * @file iterator.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_CONTAINER_INTERANL_H_
#define BASE_CONTAINER_INTERANL_H_

#include <utility>

#include "base/container/internal/iterator_traits.h"
namespace base {

template <typename IteratorImpl> struct Iterator {};

template <typename Iterator> class ReverseIterator {
public:
  using iterator_category =
      typename IteratorTraits<Iterator>::iterator_category;
  using value_type = typename IteratorTraits<Iterator>::value_type;
  using difference_type = typename IteratorTraits<Iterator>::difference_type;
  using pointer = typename IteratorTraits<Iterator>::pointer;
  using reference = typename IteratorTraits<Iterator>::reference;

  ReverseIterator() noexcept : iter_() {}

  explicit ReverseIterator(Iterator iter) noexcept : iter_(iter) {}

  // Copy
  ReverseIterator(ReverseIterator const &other) noexcept = default;
  ReverseIterator &operator=(ReverseIterator const &other) noexcept = default;

  // Converstion
  template <typename Iter>
  ReverseIterator(ReverseIterator<Iter> const &other) : iter_(other.iter_) {}
  template <typename Iter>
  ReverseIterator &operator=(ReverseIterator<Iter> const &other) {
    iter_ = other.iter_;
    return *this;
  }

  Iterator base() const noexcept { return iter_; }

  reference operator*() const {
    Iterator tmp = iter_;
    return *(--tmp);
  }

  pointer operator->() const {
    Iterator tmp = iter_;
    --tmp;
    return tmp.operator->();
  }

  ReverseIterator &operator++() {
    --iter_;
    return *this;
  }
  ReverseIterator &operator--() {
    ++iter_;
    return *this;
  }

  ReverseIterator operator++(int) {
    ReverseIterator tmp = *this;
    --iter_;
    return tmp;
  }

  ReverseIterator operator--(int) {
    ReverseIterator tmp = *this;
    ++iter_;
    return tmp;
  }

  ReverseIterator operator+(difference_type diff) {
    return ReverseIterator(iter_ - diff);
  }

  ReverseIterator &operator+=(difference_type diff) {
    iter_ -= diff;
    return *this;
  }

  ReverseIterator operator-(difference_type diff) {
    return ReverseIterator(iter_ + diff);
  }

  ReverseIterator &operator-=(difference_type diff) {
    iter_ += diff;
    return *this;
  }

private:
  Iterator iter_;
};

template <typename Iter1, typename Iter2>
inline bool operator==(ReverseIterator<Iter1> const &lhs,
                       ReverseIterator<Iter2> const &rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
inline bool operator!=(ReverseIterator<Iter1> const &lhs,
                       ReverseIterator<Iter2> const &rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
inline bool operator>(ReverseIterator<Iter1> const &lhs,
                      ReverseIterator<Iter2> const &rhs) {
  return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
inline bool operator<(ReverseIterator<Iter1> const &lhs,
                      ReverseIterator<Iter2> const &rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
inline bool operator>=(ReverseIterator<Iter1> const &lhs,
                       ReverseIterator<Iter2> const &rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
inline bool operator<=(ReverseIterator<Iter1> const &lhs,
                       ReverseIterator<Iter2> const &rhs) {
  return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
inline auto operator-(ReverseIterator<Iter1> const &lhs,
                      ReverseIterator<Iter2> const &rhs)
    -> decltype(rhs.base() - lhs.base()) {
  return rhs.base() - lhs.base();
}

template <typename Iter>
inline ReverseIterator<Iter>
operator+(typename ReverseIterator<Iter>::difference_type diff,
          ReverseIterator<Iter> const &iter) {
  return ReverseIterator<Iter>(iter.base() - diff);
}

} // namespace base
#endif