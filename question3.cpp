#include <algorithm>
#include <cmath>
#include <iostream>

using ull = unsigned long long;

template <typename T>
inline bool isPrime(const T v) {
  const T loopEnd = std::sqrt(v);
  for (T i = 2; i <= loopEnd; i++) {
    if (v % i == 0) {
      return false;
    }
  }
  return true;
}

ull getSolution(const ull num) {
  ull res = 0;
  for (ull i = 1; num / i >= i; i++) {
    if (num % i == 0) {
      if (isPrime(i)) {
        res = std::max(res, i);
      }
      if (isPrime(num / i)) {
        res = std::max(res, num / i);
      }
    }
  }
  return res;
}

int main() {
  const ull num = 600851475143;
  auto res = getSolution(num);
  std::cout << "\033[1m[Result]\033[0m: " << res << std::endl;

  return 0;
}
