/**
 * @file iterator_traits.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_CONTAINER_INTERNAL_ITERATOR_TRAITS_H_
#define BASE_CONTAINER_INTERNAL_ITERATOR_TRAITS_H_

#include <cstddef>

namespace base {

/**
 * @brief The tag of LegacyInputIterator
 *
 */
struct InputIteratorTag {};

/**
 * @brief The tag of LegacyOutputIterator
 *
 */
struct OutputIteratorTag {};

/// Forward iterators support a superset of input iterator operations.
struct ForwardIteratorTag : public InputIteratorTag {};

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct BidirectionalIteratorTag : public ForwardIteratorTag {};

/// Random-access iterators support a superset of bidirectional
/// iterator operations.
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template <typename Iterator> struct IteratorTraits {};

/**
 * @brief using for extracting traits from pointer type.
 *
 * @tparam T - value type.
 */
template <typename T> struct IteratorTraits<T *> {
  using IteratorCategory = RandomAccessIteratorTag;
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using difference_type = std::ptrdiff_t;
};

/**
 * @brief using for extracting traits from pointer-to-const type.
 *
 * @tparam T
 */
template <typename T> struct IteratorTraits<T const *> {
  using IteratorCategory = RandomAccessIteratorTag;
  using value_type = T;
  using pointer = T const *;
  using reference = T const &;
  using difference_type = std::ptrdiff_t;
};
} // namespace base
#endif