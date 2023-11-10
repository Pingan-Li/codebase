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
template <typename Iterator, typename Container> struct IteratorAdaptor {
  using iterator_type = Iterator;
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
  pointer operator*() const { return *iter_; }
  IteratorAdaptor operator++() noexcept {
    ++iter_;
    return *this;
  }

  Iterator iter_;
};

template <typename Iterator> struct ForwardIterator {};
#endif