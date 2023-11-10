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
namespace base {
template <typename Iterator> struct IteratorTraits {};
// template <typename Tp> struct IteratorTraits {};
template <typename Tp> struct IteratorTraits<Tp *> {};
} // namespace base
#endif