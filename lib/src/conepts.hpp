#include <iostream>
#include <concepts>

// concept to check if the type is printable
template <typename CustomType>
concept printable = requires(CustomType a) {
  std::cout << a;
};

// concept to check if the type is considered to be
// a number atleast within a ring
template <typename CustomType>
concept comparable_and_addible = requires(CustomType a, CustomType b) {
    a + b;
    a - b;
    a += b;
    a -= b;
    a < b;
    a <= b;
    a == b;
    a >= b;
    a > b;
    a != b;
};