#include <iostream>
#include <cmath>

using ull = unsigned long long;

template <typename NumType>
bool isPrime(const NumType value) {
  const NumType loopEnd = std::sqrt(value);
  for (NumType i = 2; i <= loopEnd; i++) {
    if (value % i == 0) {
      return false;
    }
  }
  return true;
}

decltype(auto) findNthPrime(const ull n) {
  ull all = 0, value = 1;
  do {
    value++;
    if (isPrime(value)) {
      all++;
    }
  } while (all < n);
  return value;
}

int main() {
  const ull idx = 10001;
  const auto res = findNthPrime(idx);
  std::cout << "\033[1m[Result]\033[0m: the 10001-th prime is " << res << std::endl;
  return 0;
}
