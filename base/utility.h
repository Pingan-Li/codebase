/**
 * @file utility.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 */

namespace base {

template <typename Type> Type *AddressOf(Type const &value) {
  return reinterpret_cast<Type *>(
      &const_cast<char &>(reinterpret_cast<const volatile char &>(value)));
}

} // namespace base