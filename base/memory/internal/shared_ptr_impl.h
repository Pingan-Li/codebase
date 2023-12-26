/**
 * @file shared_ptr_impl.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace base {
namespace internal {} // namespace internal
template <typename Type> class SharedPtr {
public:
  using element_type = Type;

  constexpr explicit SharedPtr() = default;

  constexpr explicit SharedPtr(std::nullptr_t) {}

  template <typename U, typename std::enable_if<
                            std::is_convertible<U *, element_type *>::value,
                            bool>::type = true>
  explicit SharedPtr(U *ptr) {}

  template <
      typename U, typename Deleter,
      typename std::enable_if<std::is_convertible<U *, element_type *>::value,
                              bool>::type = true>
  SharedPtr(U *ptr, Deleter deleter) {}

  template <class Deleter, class Alloc>
  SharedPtr(std::nullptr_t ptr, Deleter d, Alloc alloc) {}

  template <
      class U, class Deleter, class Alloc,
      typename std::enable_if<std::is_convertible<U *, element_type *>::value,
                              bool>::type = true>
  SharedPtr(U *ptr, Deleter deleter, Alloc alloc) {}

  template <class U>
  SharedPtr(SharedPtr<U> const &r, element_type *ptr) noexcept {}

  template <class Y> SharedPtr(SharedPtr<Y> &&r, element_type *ptr) noexcept {}

  SharedPtr(SharedPtr const &r) noexcept {}
  
  template <class U> SharedPtr(SharedPtr<U> const &r) noexcept {}

  SharedPtr(SharedPtr &&r) noexcept {}

  template <class U> SharedPtr(SharedPtr<U> &&r) noexcept {}

  template <class U> explicit SharedPtr(std::weak_ptr<U> const &r) {}

private:
};
} // namespace base