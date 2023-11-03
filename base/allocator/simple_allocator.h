/**
 * @file simple_allocator.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_ALLOCATOR_SIMPLE_ALLOCATOR_H_
#define BASE_ALLOCATOR_SIMPLE_ALLOCATOR_H_

#include <cstddef>
#include <cstdlib>
#include <memory>

namespace base {
template <typename T> class SimpleAllocator final {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  constexpr SimpleAllocator() noexcept = default;
  constexpr SimpleAllocator(SimpleAllocator const &other) noexcept = default;
  constexpr ~SimpleAllocator() = default;

  template <typename U>
  constexpr SimpleAllocator(SimpleAllocator<U> const &other) noexcept {};

  [[nodiscard]] constexpr T *allocate(std::size_t n) {
    return static_cast<T *>(::operator new(n * sizeof(T)));
  }

  constexpr void deallocate(T *p, std::size_t n) { ::operator delete(p); }
};

template <class T, class U>
bool operator==(const SimpleAllocator<T> &lhs,
                const SimpleAllocator<U> &rhs) noexcept {
  return true;
}

template <class T, class U>
bool operator!=(const SimpleAllocator<T> &lhs,
                const SimpleAllocator<U> &rhs) noexcept {
  return false;
}
} // namespace base
#endif