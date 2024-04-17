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
template <typename... Types> struct TypeList {};

template <typename List> struct Front;
template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
  using Type = Head;
};
template <typename List> using FrontType = typename Front<List>::Type;

template <typename List> struct PopFront {};
template <typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
  using Type = TypeList<Tail...>;
  // using Front = Head;
};
template <typename List> using PopFrontType = typename PopFront<List>::Type;

template <typename List> struct IsCopyable {};
template <typename Head, typename... Tail>
struct IsCopyable<TypeList<Head, Tail...>> {
  static constexpr bool const value = std::is_copy_assignable<Head>::value &&
                                      IsCopyable<TypeList<Tail...>>::value;
};
template <typename Last> struct IsCopyable<TypeList<Last>> {
  static constexpr bool const value = std::is_copy_assignable<Last>::value;
};

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
  using Parameter = base::meta::TypeList<std::string, int, double>;
  using Result = base::meta::TypeList<int, double>;
  static_assert(
      std::is_same<base::meta::PopFrontType<Parameter>, Result>::value, "OK");
}

TEST(IsCopyable, Case0) {
  static_assert(
      base::meta::IsCopyable<base::meta::TypeList<char, int, double>>::value,
      "OK");
  static_assert(
      not base::meta::IsCopyable<base::meta::TypeList<std::thread>>::value,
      "OK");
}