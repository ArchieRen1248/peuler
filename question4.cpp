#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

using ull = unsigned long long;

template <typename NumType>
decltype(auto) splitNumber(NumType num) {
  std::vector<uint8_t> vec{};
  while (num) {
    vec.emplace_back(num % 10);
    num /= 10;
  }
  return vec;
}

bool isPalindrome(const std::vector<uint8_t> &vec) {
  for (decltype(vec.size()) i = 0, j = vec.size() - 1; i < j; i++, j--) {
    if (vec[i] != vec[j]) {
      return false;
    }
  }
  return true;
}

ull largestPalindrome(const uint8_t bitNum) {
  ull res = 0;
  const size_t start = std::pow(10, bitNum - 1), end = start * 10 - 1;
  for (ull i = start; i <= end; i++) {
    for (ull j = start; j <= end; j++) {
      if (isPalindrome(splitNumber(i * j))) {
        res = std::max(res, i * j);
      }
    }
  }
  return res;
}

int main() {
  std::cout << "\033[1m[Result]\033[0m: " << largestPalindrome(2) << std::endl;
  std::cout << "\033[1m[Result]\033[0m: " << largestPalindrome(3) << std::endl;

  return 0;
}
