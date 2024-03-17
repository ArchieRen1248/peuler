#include <iostream>
#include <set>
#include <vector>

using ull = unsigned long long;

template <typename ScopeType, typename ValueType>
decltype(auto) getSumOfMultiple(const ScopeType scope,
                                const std::vector<ValueType> &multiple) {
  std::set<ScopeType> set{};
  for (const auto &v : multiple) {
    for (ScopeType i = 0; i * v < scope; i++) {
      set.insert(i * v);
    }
  }
  ScopeType sum = 0;
  for (const auto &v : set) {
    sum += v;
  }
  return sum;
}

int main() {
  ull scope = 1000;
  std::vector<unsigned int> multiple{3, 5};
  auto res = getSumOfMultiple(scope, multiple);

  std::cout << "\033[1m[Result]\033[0m: " << res << std::endl;

  return 0;
}
