#include "base/closure.h"
#include <iostream>
#include <type_traits>

namespace base {

void PlainFunction() { std::cout << "Hello world"; }

int PlainFunction1(int a, int b) {
  std::cout << a << " + " << b << " = " << a + b;
  return a + b;
}

void TestPlainfunction() {

  auto closure = base::MakeClosure(PlainFunction1, 4, 2);
  auto result = std::move(closure)();
  std::cout << (std::is_same<decltype(result), int &>::value);

  std::invoke_result<int (&)(int, int), int, int>::type a = 1;
}

} // namespace base

int main(int argc, char **argv) {
  base::TestPlainfunction();
  return 0;
}
