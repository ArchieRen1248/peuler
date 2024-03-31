#include <iostream>
#include <ostream>

#include "bigint.hpp"

using namespace utils;

int main() {
  BigInt a{0};
  std::cout << a << std::endl;

  BigInt b1{"121234345656787812123434565678781212343456567878"};
  std::cout << b1 << std::endl;
  BigInt b2{"-121234345656787812123434565678781212343456567878"};
  std::cout << b2 << std::endl;
  // BigInt b3{"-12A234345656787812123434565678781212343456567878"};
  // std::cout << b3 << std::endl;

  BigInt c{-123456789123456789};
  std::cout << c << std::endl;

  BigInt d{-c};
  std::cout << d << std::endl;

  BigInt e = b1;
  std::cout << e << ", " << b1 << std::endl;

  b2 = c;
  std::cout << b2 << ", " << c << std::endl;

  std::cout << (b2 == c) << std::endl;
  std::cout << (b2 == d) << std::endl;
  std::cout << (b2 == (-123456789123456789)) << std::endl;
  std::cout << (b2 == (-100)) << std::endl;
  std::cout << (b2 != (-100)) << std::endl;

  std::cout << (b1 > b2) << std::endl;
  std::cout << (b2 > c) << std::endl;
  std::cout << (c > b2) << std::endl;

  std::cout << (c + d) << std::endl;

  std::cout << c << std::endl;
  std::cout << (c + 100) << std::endl;
  std::cout << (c - 100) << std::endl;
  std::cout << (d + BigInt{"100000"}) << std::endl;

  BigInt m1{"12341234"};
  std::cout << m1 * m1 << std::endl;
  BigInt m2{"123412341234"};
  std::cout << m2 * m2 << std::endl;

  return 0;
}
