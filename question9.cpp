#include <tuple>
#include <iostream>

decltype(auto) getSolution(const unsigned int sum) {
  unsigned int a = 1, b = 1, c = 1;
  for (; a <= sum / 2; a++) {
    for (b = a + 1; b <= sum; b++) {
      c = sum - a - b;
      if (!(a < b && b < c)) {
        break;
      }
      if (a * a + b * b == c * c) {
        return std::make_tuple(a, b, c);
      }
    }
  }
  return std::make_tuple(0U, 0U, 0U);
}

template <typename T>
static inline const std::string spaceBar(const T len) {
  std::string str = "";
  for (T i = 0; i < len; i++) {
    str += " ";
  }
  return str;
}

int main() {
  const unsigned int sum = 1000;
  const auto res = getSolution(sum);
  auto a = std::get<0>(res), b = std::get<1>(res), c = std::get<2>(res);
  if (a == 0 && b == 0 && c == 0) {
    std::cout << "\033[1m[Result]\033[0m: no answer." << std::endl;
  } else {
    std::cout << "\033[1m[Result]\033[0m: " <<  "a = " << a << std::endl
              << spaceBar(10) << "b = " << b << std::endl
              << spaceBar(10) << "c = " << c << std::endl
              << spaceBar(10) << "a * b * c = " << a * b * c
              << std::endl;
  }

  return 0;
}
