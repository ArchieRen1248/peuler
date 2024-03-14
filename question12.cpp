#include <iostream>
#include <algorithm>
#include <cassert>

using ull = unsigned long long;

template <typename ValueType>
decltype(auto) numberOfDivisor(const ValueType v) {
  assert(v >= 1);
  if (v == 1) {
    return 1U;
  }
  unsigned int divisorNum = 0;
  ValueType loopEnd = v;
  for (ValueType i = 1; i < loopEnd; i++) {
    if (v % i == 0) {
      divisorNum += 2;
      loopEnd = std::max(i, v / i);
    }
  }
  return divisorNum;
}

decltype(auto) getSolution(const unsigned int limit) {
  ull value = 1, step = 2;
  while (numberOfDivisor(value) <= limit) {
    value += step;
    step++;
  }
  return value;
}

int main() {
  const unsigned int limit = 500;
  std::cout << "\033[1m[Result]\033[0m: "
            << getSolution(limit)
            << std::endl;

  return 0;
}
