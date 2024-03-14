#include <iostream>

using ull = unsigned long long;

static inline ull sumOfSquare(const ull scope) {
  ull v = 0;
  for (ull i = 1; i <= scope; i++) {
    v += i * i;
  }
  return v;
}

static inline ull squareOfSum(const ull scope) {
  ull v = 0;
  for (ull i = 1; i <= scope; i++) {
    v += i;
  }
  return v * v;
}

ull squareDifference(const ull scope) {
  return squareOfSum(scope) - sumOfSquare(scope);
}

int main() {
  auto res = squareDifference(100);
  std::cout << "\033[1m[Result]\033[0m: " << res << std::endl;

  return 0;
}
