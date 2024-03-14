#include <chrono>
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

ull sumOfPrimeBelow(const ull scope) {
  ull res = 0;
  for (ull i = 2; i < scope; i++) {
    if (isPrime(i)) {
      res += i;
    }
  }
  return res;
}

int main() {
  const ull scope = 2000000;

  auto timeStart = std::chrono::system_clock::now();
  const auto res = sumOfPrimeBelow(scope);
  auto timeEnd = std::chrono::system_clock::now();

  std::cout << "\033[1m[Result]\033[0m: "
            << "sum of primes below " << scope
            << " is " << res << std::endl;

  std::cout << "\033[1m[Duration test]\033[0m: consume "
            << std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count()
            << " us"
            << std::endl;

  return 0;
}
