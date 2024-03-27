#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

#define ESC_NORMAL_TEXT "\033[0m"
#define ESC_BOLD_TEXT "\033[1m"
#define ESC_HIGHLIGHT_TEXT "\033[7m"

using ull = unsigned long long;

template <typename ValueType>
inline bool IsPrime(ValueType v) {
  ValueType loopEnd = std::sqrt(v);
  for (ValueType i = 2; i <= loopEnd; i++) {
    if (v % i == 0) return false;
  }
  return true;
}

template <typename T>
inline decltype(auto) GetPrimeTable(T scope) {
  std::vector<T> res{};
  for (T i = 2; i <= scope; i++) {
    if (IsPrime(i)) res.push_back(i);
  }
  return res;
}

ull GetSolution(ull scope) {
  auto primeTable = GetPrimeTable(scope);
  ull res = 1;
  std::map<ull, ull> resMap;

  for (size_t i = 1; i <= scope; i++) {
    std::map<ull, ull> currMap;
    for (const auto &v : primeTable) {
      auto currNum = i;
      while (currNum % v == 0) {
        currMap[v]++;
        currNum /= v;
      }
    }
    for (const auto &v : currMap) {
      resMap[v.first] = std::max(v.second, resMap[v.first]);
    }
  }

  for (auto &v : resMap) {
    while (v.second > 0) {
      res *= v.first;
      v.second--;
    }
  }

  return res;
}

int main() {
  auto input1 = 10, input2 = 20;
  auto res1 = GetSolution(input1);
  auto res2 = GetSolution(input2);

  std::cout << ESC_BOLD_TEXT << "[Result]" << ESC_NORMAL_TEXT << " Result("
            << input1 << ") = " << res1 << std::endl;
  std::cout << ESC_BOLD_TEXT << "[Result]" << ESC_NORMAL_TEXT << " Result("
            << input2 << ") = " << res2 << std::endl;

  return 0;
}
