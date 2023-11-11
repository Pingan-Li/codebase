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
#include "base/container/internal/iterator_traits.h"
template <typename IteratorImpl, typename Container> struct Iterator {
  using iterator_type = IteratorImpl;
  using value_type = typename iterator_type::value_type;
  using pointer = typename iterator_type::pointer;
  using reference = typename iterator_type::reference;
  using difference_type = typename iterator_type::difference_type;

  // typedef _Iter iterator_type; typedef typename
  // iterator_traits<iterator_type>::value_type        value_type; typedef
  // typename iterator_traits<iterator_type>::difference_type   difference_type;
  // typedef typename iterator_traits<iterator_type>::pointer           pointer;
  // typedef typename iterator_traits<iterator_type>::reference reference;
  // typedef typename iterator_traits<iterator_type>::iterator_category
  // iterator_category;

  /**
   * @brief default constructor
   *
   */
  Iterator() noexcept : iter_() {}

  Iterator(IteratorImpl const &iterator_impl) = default;

  Iterator &operator=(IteratorImpl const &iterator_impl) = default;

  ~Iterator() = default;

  reference operator*() const { return *iter_; }
  Iterator operator++() noexcept {
    ++iter_;
    return *this;
  }

private:
  IteratorImpl iter_;
};

template <typename Iterator> class ReverseIterator {
  using Base = Iterator;
  using IteratorCategory =
      typename base::IteratorTraits<Iterator>::IteratorCategory;
  using value_type = typename base::IteratorTraits<Base>::value_type;
  using pointer = typename base::IteratorTraits<Base>::pointer;
  using reference = typename base::IteratorTraits<Base>::reference;
  using difference_type = typename base::IteratorTraits<Base>::difference_type;

  ReverseIterator(Base iter) : iter_(iter) {}
  ReverseIterator(Base const &iter) : iter_(iter) {}

private:
  Base iter_;
};

// template <typename IteratorImpl> struct ForwardIterator {
//   using iterator_type = IteratorImpl;
//   using value_type = typename iterator_type::value_type;
//   using pointer = typename iterator_type::pointer;
//   using reference = typename iterator_type::reference;
//   using difference_type = typename iterator_type::difference_type;
// };
#endif