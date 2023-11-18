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

template <typename Iterator> class GenericIterator {
public:
  using iterator_type = Iterator;
  using Traits = IteratorTraits<iterator_type>;
  using iterator_category = typename Traits::iterator_category;
  using value_type = typename Traits::value_type;
  using pointer = typename Traits::pointer;
  using reference = typename Traits::reference;
  using difference_type = typename Traits::difference_type;

  /**
   * @brief Default constructor.
   *
   */
  GenericIterator() noexcept : iterator_() {}

  /**
   * @brief Constructor with const &iter
   *
   * @param iter - actually iterator.
   */
  explicit GenericIterator(iterator_type const &iter) noexcept
      : iterator_(iter) {}

  template <typename Iter>
  explicit GenericIterator(GenericIterator<Iter> const &iterator) noexcept
      : iterator_(iterator.base()) {}

  iterator_type base() const noexcept { return iterator_; }

  reference operator*() const noexcept { return *iterator_; }

  pointer operator->() const noexcept { return iterator_; }

  reference operator[](difference_type diff) const noexcept {
    return iterator_[diff];
  }

  GenericIterator &operator++() noexcept {
    ++iterator_;
    return *this;
  }

  GenericIterator &operator--() noexcept {
    --iterator_;
    return *this;
  }

  GenericIterator operator++(int) noexcept {
    return GenericIterator(iterator_++);
  }

  GenericIterator operator--(int) noexcept {
    return GenericIterator(iterator_--);
  }

  GenericIterator &operator+=(difference_type diff) noexcept {
    iterator_ += diff;
    return *this;
  }

  GenericIterator &operator-=(difference_type diff) noexcept {
    iterator_ -= diff;
    return *this;
  }

  GenericIterator operator+(difference_type diff) const noexcept {
    return GenericIterator(iterator_ + diff);
  }

  GenericIterator operator-(difference_type diff) const noexcept {
    return GenericIterator(iterator_ - diff);
  }

private:
  Iterator iterator_;
};

template <typename Iterator> class GenericReverseIterator {
public:
  using iterator_type = Iterator;
  using Traits = IteratorTraits<iterator_type>;
  using iterator_category = typename Traits::iterator_category;
  using value_type = typename Traits::value_type;
  using pointer = typename Traits::pointer;
  using reference = typename Traits::reference;
  using difference_type = typename Traits::difference_type;

  GenericReverseIterator() noexcept : iterator_() {}

  GenericReverseIterator(Iterator const iterator) : iterator_(iterator) {}

  template <typename Iter>
  GenericReverseIterator(GenericReverseIterator<Iter> const iterator)
      : iterator_(iterator.iterator_) {}

  template <typename Iter>
  GenericReverseIterator &
  operator=(GenericReverseIterator<Iter> const &iterator) {
    iterator_ = iterator.iterator_;
    return *this;
  }

  Iterator base() const noexcept { return iterator_; }

  reference operator*() const noexcept {
    Iterator tmp = iterator_;
    return *(--tmp);
  }

  pointer operator->() const noexcept {
    Iterator tmp = iterator_;
    return (--tmp).operator->();
  }

  reference operator[](difference_type diff) const {
    return *(iterator_ - diff);
  }

  GenericReverseIterator &operator++() noexcept {
    --iterator_;
    return *this;
  }

  GenericReverseIterator operator++(int) noexcept {
    Iterator tmp = iterator_;
    --iterator_;
    return GenericReverseIterator(iterator_);
  }

  GenericReverseIterator &operator--() noexcept {
    ++iterator_;
    return *this;
  }

  GenericReverseIterator operator--(int) noexcept {
    Iterator tmp = iterator_;
    ++tmp;
    return tmp;
  }

  GenericReverseIterator operator+(difference_type diff) const noexcept {
    return GenericReverseIterator(iterator_ - diff);
  }

  GenericReverseIterator &operator+=(difference_type diff) noexcept {
    iterator_ -= diff;
    return *this;
  }

  GenericReverseIterator operator-(difference_type diff) const noexcept {
    return GenericReverseIterator(iterator_ + diff);
  }

  GenericReverseIterator &operator-=(difference_type diff) noexcept {
    iterator_ += diff;
    return *this;
  }

private:
  Iterator iterator_;
};

template <typename L, typename R>
constexpr inline bool operator==(GenericIterator<L> const &lhs,
                                 GenericIterator<R> const &rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iterator>
constexpr inline bool operator==(GenericIterator<Iterator> const &lhs,
                                 GenericIterator<Iterator> const &rhs) {
  return lhs.base() == rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator!=(GenericIterator<L> const &lhs,
                                 GenericIterator<R> const &rhs) {
  return lhs.base() != rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator<(GenericIterator<L> const &lhs,
                                GenericIterator<R> const &rhs) {
  return lhs.base() < rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator<=(GenericIterator<L> const &lhs,
                                 GenericIterator<R> const &rhs) {
  return lhs.base() <= rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator>(GenericIterator<L> const &lhs,
                                GenericIterator<R> const &rhs) {
  return lhs.base() > rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator>=(GenericIterator<L> const &lhs,
                                 GenericIterator<R> const &rhs) {
  return lhs.base() >= rhs.base();
}

template <typename L, typename R>
constexpr inline auto operator-(GenericIterator<L> const &lhs,
                                GenericIterator<R> const &rhs)
    -> decltype(lhs.base() - rhs.base()) {
  return lhs.base() - rhs.base();
}

template <typename Iterator>
constexpr inline typename GenericIterator<Iterator>::difference_type
operator-(GenericIterator<Iterator> const &lhs,
          GenericIterator<Iterator> const &rhs) {
  return lhs.base() - rhs.base();
}

template <typename Iterator>
constexpr inline GenericIterator<Iterator>
operator+(typename GenericIterator<Iterator>::difference_type diff,
          GenericIterator<Iterator> const &iterator) {
  return GenericIterator(iterator.base() + diff);
}

template <typename L, typename R>
constexpr inline bool operator==(GenericReverseIterator<L> const &lhs,
                                 GenericReverseIterator<R> const &rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iterator>
constexpr inline bool operator==(GenericReverseIterator<Iterator> const &lhs,
                                 GenericReverseIterator<Iterator> const &rhs) {
  return lhs.base() == rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator!=(GenericReverseIterator<L> const &lhs,
                                 GenericReverseIterator<R> const &rhs) {
  return lhs.base() != rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator<(GenericReverseIterator<L> const &lhs,
                                GenericReverseIterator<R> const &rhs) {
  return lhs.base() > rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator<=(GenericReverseIterator<L> const &lhs,
                                 GenericReverseIterator<R> const &rhs) {
  return lhs.base() >= rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator>(GenericReverseIterator<L> const &lhs,
                                GenericReverseIterator<R> const &rhs) {
  return lhs.base() < rhs.base();
}

template <typename L, typename R>
constexpr inline bool operator>=(GenericReverseIterator<L> const &lhs,
                                 GenericReverseIterator<R> const &rhs) {
  return lhs.base() <= rhs.base();
}

template <typename L, typename R>
constexpr inline auto operator-(GenericReverseIterator<L> const &lhs,
                                GenericReverseIterator<R> const &rhs)
    -> decltype(rhs.base() - lhs.base()) {
  return rhs.base() - lhs.base();
}

template <typename Iterator>
constexpr inline GenericReverseIterator<Iterator>
operator+(typename GenericReverseIterator<Iterator>::difference_type diff,
          GenericReverseIterator<Iterator> const &iterator) {
  return GenericReverseIterator(iterator.base() - diff);
}

} // namespace base
#endif