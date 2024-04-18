/**
 * @file type_list.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "testing/googletest/include/gtest/gtest.h"

#include <thread>
#include <type_traits>

namespace base {
namespace meta {
template <typename... Types> struct TypeList;

template <typename List> struct Front;
template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
  using Type = Head;
};
template <typename List> using FrontType = typename Front<List>::Type;

template <typename List> struct PopFront;
template <typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
  using Type = TypeList<Tail...>;
  // using Front = Head;
};
template <typename List> using PopFrontType = typename PopFront<List>::Type;

template <typename Head, typename List> struct PushFront;
template <typename Head, typename... Tail>
struct PushFront<Head, TypeList<Tail...>> {
  using Type = TypeList<Head, Tail...>;
};

template <typename List> struct IsCopyable;
template <typename Head, typename... Tail>
struct IsCopyable<TypeList<Head, Tail...>> {
  static constexpr bool const value = std::is_copy_assignable<Head>::value &&
                                      IsCopyable<TypeList<Tail...>>::value;
};
template <typename Last> struct IsCopyable<TypeList<Last>> {
  static constexpr bool const value = std::is_copy_assignable<Last>::value;
};

template <typename List> struct Length;
template <typename Head, typename... Tail>
struct Length<TypeList<Head, Tail...>> {
  static constexpr std::size_t value = 1 + Length<TypeList<Tail...>>::value;
};
template <> struct Length<TypeList<>> {
  static constexpr std::size_t value = 0;
};

// Variable template partial specialization.
template <typename Type> constexpr std::size_t Size = sizeof(Type);
template <typename Type> constexpr std::size_t Size<Type &> = sizeof(Type);
template <typename Type> constexpr std::size_t Size<Type &&> = sizeof(Type);

} // namespace meta
} // namespace base

class TypeListTest : public testing::Test {
public:
private:
};

TEST_F(TypeListTest, Front) {
  static_assert(
      std::is_same<
          base::meta::FrontType<base::meta::TypeList<int, double, char>>,
          int>::value,
      "OK");
}

TEST_F(TypeListTest, PopFront) {
  using List = base::meta::TypeList<std::string, int, double>;
  using Result = base::meta::TypeList<int, double>;
  static_assert(std::is_same<base::meta::PopFrontType<List>, Result>::value,
                "OK");
  using ZeroElementList = base::meta::TypeList<>;
  static_assert(std::is_same<base::meta::PushFront<int, ZeroElementList>::Type,
                             base::meta::TypeList<int>>::value,
                "OK");
}

TEST_F(TypeListTest, PushFront) {
  using List = base::meta::TypeList<int>;
  using NewList = base::meta::PushFront<double, List>::Type;
  using Result = base::meta::TypeList<double, int>;
  static_assert(std::is_same<NewList, Result>::value, "OK");
}

TEST_F(TypeListTest, Size) {
  static_assert(base::meta::Size<int> == sizeof(int), "OK");
  static_assert(base::meta::Size<double &> == base::meta::Size<double &&>,
                "OK");
}

TEST_F(TypeListTest, Length) {
  using ZeroElementList = base::meta::TypeList<>;
  using SingleElementList = base::meta::TypeList<int>;
  static_assert(base::meta::Length<ZeroElementList>::value == 0, "OK");
  static_assert(base::meta::Length<SingleElementList>::value == 1, "OK");
}

TEST(IsCopyable, IsCopyable) {
  static_assert(
      base::meta::IsCopyable<base::meta::TypeList<char, int, double>>::value,
      "OK");
  static_assert(
      not base::meta::IsCopyable<base::meta::TypeList<std::thread>>::value,
      "OK");
}