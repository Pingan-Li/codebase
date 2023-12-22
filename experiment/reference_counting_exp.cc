/**
 * @file reference_counting_exp.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>

namespace base {
template <typename Type> class Pointer {
public:
  using value_type = Type;
  using pointer = value_type *;
  using const_pointer = value_type const *;
  using reference = value_type &;
  using const_reference = value_type const &;

  Pointer() noexcept : pointer_(nullptr) {}

  explicit Pointer(std::nullptr_t) noexcept : pointer_(nullptr) {}

  explicit Pointer(pointer ptr) : pointer_(ptr) {}

  pointer operator->() noexcept { return pointer_; }

  const_pointer operator->() const noexcept { return pointer_; }

  reference operator*() noexcept { return *pointer_; }

  const_reference operator*() const noexcept { return *pointer_; }

  bool operator==(nullptr_t) const noexcept { return pointer_ == nullptr; }

  template <typename U> bool operator==(Pointer<U> ptr) {
    return pointer_ == ptr.pointer_;
  }

private:
  pointer pointer_;
};

template <typename Type> struct CountingTraits {};

template <typename Type> class RefCnt {
public:
  RefCnt() noexcept : cnt_(1) {}

  void Increase() const noexcept { ++cnt_; }

  bool Decrease() const noexcept {
    --cnt_;
    if (cnt_ == 0) {
      delete this;
      return true;
    }
    return false;
  }

  int Count() const noexcept { return cnt_; }

  ~RefCnt() { std::cout << "Bye-bye~\n"; }

private:
  int mutable cnt_;
};

class A : public RefCnt<A> {
public:
  A() noexcept {}
};

template <typename Type, typename... Args>
auto MakeRefCnt(Args &&...args) -> Pointer<Type> {
  return Pointer<Type>(new Type(std::forward<Args>(args)...));
}
} // namespace base

int main(int argc, char **argv) {
  base::Pointer<base::A> ptr = base::MakeRefCnt<base::A>();
  assert(ptr->Count() == 1);
  ptr->Decrease();
  // Oops
  std::cout << (*ptr).Count() << std::endl;
}