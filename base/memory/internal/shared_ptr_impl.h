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

#include <atomic>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "base/cxx.h"

namespace base {
namespace internal {} // namespace internal
template <typename Type> class SharedPtr {
public:
#if SINCE(CXX_17)
  using element_type = std::remove_extent_t<Type>;
  using weak_type = std::weak_ptr<Type>;
#else
  using element_type = Type;
#endif
  /**
   * @brief Constructs a shared_ptr with no managed object, i.e. empty
   * shared_ptr.
   *
   */

  constexpr explicit SharedPtr() {
    // C.1
  }
  constexpr explicit SharedPtr(std::nullptr_t) {
    // C.2
  }

  /**
   * @brief Constructs a shared_ptr with ptr as the pointer to the managed
   * object.
   *
   * @tparam U - U* must be convertible to Type*.
   * @param ptr
   */
  template <typename U, typename std::enable_if<
                            std::is_convertible<U *, element_type *>::value,
                            bool>::type = true>
  explicit SharedPtr(U *ptr) {
    // C.3
    auto *str = new Storage;
    str->shared_count_.fetch_add(1, std::memory_order_acq_rel);
    storage_.store(str, std::memory_order_release);
  }

  template <
      typename U, typename Deleter,
      typename std::enable_if<std::is_convertible<U *, element_type *>::value,
                              bool>::type = true,
      typename std::enable_if<std::is_copy_constructible<Deleter>::value,
                              bool>::type = true>
  SharedPtr(U *ptr, Deleter deleter) {
    // C.4
    auto *str = new Storage;
    str->shared_count_.fetch_add(1, std::memory_order_acq_rel);
    storage_.store(str, std::memory_order_release);
    auto *deleter_impl = DeleterImpl<Deleter>(std::move(deleter));
    deleter_base_.store(deleter_impl, std::memory_order_release);
  }

  template <class Deleter,
            typename std::enable_if<std::is_copy_constructible<Deleter>::value,
                                    bool>::type = true>
  SharedPtr(std::nullptr_t ptr, Deleter d) {
    // C.5
  }

  template <
      class U, class Deleter, class Alloc,
      typename std::enable_if<std::is_convertible<U *, element_type *>::value,
                              bool>::type = true,
      typename std::enable_if<std::is_copy_constructible<Deleter>::value,
                              bool>::type = true>
  SharedPtr(U *ptr, Deleter deleter, Alloc alloc) {
    // C.6
    auto *str = new Storage;
    str->shared_count_.fetch_add(1, std::memory_order_acq_rel);
    storage_.store(str, std::memory_order_release);
    auto *deleter_impl = new DeleterImpl<Deleter>(std::move(deleter));
    deleter_base_.store(deleter_impl, std::memory_order_release);
    std::ignore = alloc;
  }

  template <class Deleter, class Alloc,
            typename std::enable_if<std::is_copy_constructible<Deleter>::value,
                                    bool>::type = true>
  SharedPtr(std::nullptr_t ptr, Deleter d, Alloc alloc) {
    // C.7
    auto *deleter_impl = new DeleterImpl<Deleter>(std::move(d));
    deleter_base_.store(deleter_impl, std::memory_order_release);
    std::ignore = alloc;
  }

  /**
   * @brief The aliasing constructor: constructs a shared_ptr which shares
   * ownership information with the initial value of r, but holds an unrelated
   * and unmanaged pointer ptr. If this shared_ptr is the last of the group to
   * go out of scope, it will call the stored deleter for the object originally
   * managed by r. However, calling get() on this shared_ptr will always return
   * a copy of ptr. It is the responsibility of the programmer to make sure that
   * this ptr remains valid as long as this shared_ptr exists, such as in the
   * typical use cases where ptr is a member of the object managed by r or is an
   * alias (e.g., downcast) of r.get() For the second overload taking an rvalue,
   * r is empty and r.get() == nullptr after the call.(since C++20)
   *
   * @tparam U
   * @tparam std::enable_if<std::is_convertible<U *, Type *>::value,
   * bool>::type
   * @param r
   * @param ptr
   */
  template <typename U,
            typename std::enable_if<std::is_convertible<U *, Type *>::value,
                                    bool>::type = true>
  SharedPtr(SharedPtr<U> const &r, element_type *ptr) noexcept {
    // C.8
  }

  /**
   * @brief Constructs a shared_ptr which shares ownership of the object managed
   * by r. If r manages no object, *this manages no object either. The template
   * overload doesn't participate in overload resolution if Y* is not implicitly
   * convertible to(until C++17)compatible with(since C++17) T*.
   *
   * @tparam U
   * @param r
   * @param ptr
   */
  template <class U> SharedPtr(SharedPtr<U> &&r, element_type *ptr) noexcept {
    // C.8
  }

  SharedPtr(SharedPtr const &r) noexcept {
    // C.9
  }
  /**
   * @brief Construct a new Shared Ptr object
   *
   * @tparam U
   * @param r
   */
  template <class U> SharedPtr(SharedPtr<U> const &r) noexcept {
    // C.9
  }

  SharedPtr(SharedPtr &&r) noexcept {
    // C.10
  }
  template <class U> SharedPtr(SharedPtr<U> &&r) noexcept {
    // C.10
  }

  /**
   * @brief Constructs a shared_ptr which shares ownership of the object
   * managed by r. Y* must be implicitly convertible to T*.(until C++17)This
   * overload participates in overload resolution only if Y* is compatible
   * with T*.(since C++17) Note that r.lock() may be used for the same
   * purpose: the difference is that this constructor throws an exception if
   * the argument is empty, while std::weak_ptr<T>::lock() constructs an empty
   * std::shared_ptr in that case
   *
   * @tparam U
   * @param r
   */
  template <typename U,
            typename std::enable_if<std::is_convertible<U *, Type *>::value,
                                    bool>::type = true>
  explicit SharedPtr(std::weak_ptr<U> const &r) {
    // C.11
  }

  /**
   * @brief Constructs a shared_ptr which manages the object currently managed
   * by r. The deleter associated with r is stored for future deletion of the
   * managed object. r manages no object after the call.
   *
   * @tparam U
   * @tparam Deleter
   * @param r
   */
  template <typename U, typename Deleter,
            typename std::enable_if<std::is_convertible<U *, Type *>::value,
                                    bool>::type = true,
            typename std::enable_if<std::is_copy_constructible<Deleter>::value,
                                    bool>::type = true>
  SharedPtr(std::unique_ptr<U, Deleter> &&r) {
    // C.13
  }

  ~SharedPtr() {
    if (deleter_base_) {
      deleter_base_.load()->Delete(storage_.load()->elememt_);
      delete deleter_base_.load();
    } else {
      delete storage_.load()->elememt_;
    }
    delete storage_.load();
  }

private:
  void __clear() {
    // TODO
  }

  struct Storage {
    std::atomic<int> shared_count_ = 0;
    std::atomic<int> weak_count_ = 0;
    element_type *elememt_ = nullptr;
  };

  struct DeleterBase {
    virtual void Delete(void *pointer) = 0;

    virtual ~DeleterBase() = default;
  };

  template <typename Deleter> struct DeleterImpl : public Deleter {
    DeleterImpl(Deleter deleter) : deleter_(std::move(deleter)) {}

    void Delete(void *pointer) {
      deleter_(static_cast<element_type *>(pointer));
    }
    Deleter deleter_;
  };

  std::atomic<Storage *> storage_ = nullptr;
  std::atomic<DeleterBase *> deleter_base_ = nullptr;
};
} // namespace base