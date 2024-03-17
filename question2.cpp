#include <iostream>

using ull = unsigned long long;

template <typename T>
static inline bool isEven(const T v) {
  return v % 2 == 0;
}

ull getSolution(const ull limit) {
  ull res = 0;
  ull v1 = 1, v2 = 2;
  while (v2 <= limit) {
    if (isEven(v2)) {
      res += v2;
    }
    auto tmp = v1;
    v1 = v2;
    v2 = v1 + tmp;
  }

  return res;
}

int main() {
  const ull limit = 4000000;
  auto res = getSolution(limit);
  std::cout << "\033[1m[Result]\033[0m: " << res << std::endl;

  return 0;
}
