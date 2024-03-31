#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace utils {
class BigInt {
 public:
  using ElemType_t = int8_t;

  explicit BigInt(const std::string &numStr) {
    isPositive_ = true;
    size_t idxStart = 0;
    if (numStr[0] == '+' || numStr[0] == '-') {
      isPositive_ = numStr[0] == '+';
      idxStart = 1;
    }
    for (size_t i = numStr.size(); i > idxStart; i--) {
      if (numStr[i - 1] < '0' || numStr[i - 1] > '9') {
        throw "Must init BigInt with string only consist of numbers or +/-";
      }
      numVec_.push_back(numStr[i - 1] - '0');
    }
  }
  explicit BigInt(long long number) {
    isPositive_ = true;
    if (number < 0) {
      isPositive_ = false;
      number *= -1;
    }
    while (number > 0) {
      numVec_.push_back(number % 10);
      number /= 10;
    }
    if (numVec_.size() == 0) numVec_.push_back(0);
  }
  BigInt(const BigInt &rhs) : numVec_{rhs.numVec_}, isPositive_{rhs.isPositive_} {}
  ~BigInt() {}

  bool operator==(const BigInt &rhs) const {
    if (isPositive_ != rhs.isPositive_ || numVec_.size() != rhs.numVec_.size())
      return false;
    for (size_t i = 0; i < numVec_.size(); i++) {
      if (numVec_[i] != rhs.numVec_[i]) return false;
    }
    return true;
  }
  bool operator==(const long long rhs) const { return *this == BigInt(rhs); }
  friend bool operator==(const long long lhs, const BigInt &rhs) {
    return rhs == lhs;
  }

  bool operator!=(const BigInt &rhs) const { return !(*this == rhs); }
  bool operator!=(const long long rhs) const { return *this != BigInt(rhs); }
  friend bool operator!=(const long long lhs, const BigInt &rhs) {
    return rhs != lhs;
  }

  bool operator>(const BigInt &rhs) const {
    if (isPositive_ == true && rhs.isPositive_ == false) return true;
    if (isPositive_ == false && rhs.isPositive_ == true) return false;
    if (isPositive_ == true) {
      if (numVec_.size() != rhs.numVec_.size())
        return numVec_.size() > rhs.numVec_.size();
      else {
        for (size_t i = numVec_.size(); i > 0; i--) {
          if (numVec_[i] != rhs.numVec_[i]) {
            return numVec_[i] > rhs.numVec_[i];
          }
        }
      }
    } else {
      return -(*this) <= rhs;
    }
    return false;
  }
  bool operator>(const long long rhs) const { return *this > BigInt(rhs); }
  friend bool operator>(const long long lhs, const BigInt &rhs) {
    return BigInt{lhs} > rhs;
  }

  bool operator>=(const BigInt &rhs) const { return *this > rhs || *this == rhs; }
  bool operator>=(const long long rhs) const { return *this >= BigInt(rhs); }
  friend bool operator>=(const long long lhs, const BigInt &rhs) {
    return BigInt(lhs) >= rhs;
  }

  bool operator<(const BigInt &rhs) const { return !(*this >= rhs); }
  bool operator<(const long long rhs) const { return *this < BigInt(rhs); }
  friend bool operator<(const long long lhs, const BigInt &rhs) {
    return BigInt(lhs) < rhs;
  }

  bool operator<=(const BigInt &rhs) const { return !(*this > rhs); }
  bool operator<=(const long long rhs) const { return *this <= BigInt(rhs); }
  friend bool operator<=(const long long lhs, const BigInt &rhs) {
    return BigInt(lhs) <= rhs;
  }

  BigInt &operator=(const BigInt &rhs) {
    isPositive_ = rhs.isPositive_;
    numVec_ = std::vector<ElemType_t>{rhs.numVec_};
    return *this;
  }
  BigInt &operator=(const long long rhs) { return operator=(BigInt{rhs}); }

  BigInt operator+(const BigInt &rhs) const {
    // lhs(+) + rhs(+)
    if (isPositive_ == true && rhs.isPositive_ == false) {
      // lhs(+) + rhs(-)
      return *this - (-rhs);
    } else if (isPositive_ == false && rhs.isPositive_ == true) {
      // lhs(-) + rhs(+)
      return rhs - (-(*this));
    } else {
      // lhs(-) + rhs(-)  or  lhs(-) + rhs(-)
      BigInt res{};
      ElemType_t t = 0;
      auto loopEnd = std::max(numVec_.size(), rhs.numVec_.size());
      decltype(loopEnd) i = 0;
      while (t != 0 || i < loopEnd) {
        if (i < numVec_.size()) t += numVec_[i];
        if (i < rhs.numVec_.size()) t += rhs.numVec_[i];
        res.numVec_.push_back(t % 10);
        t /= 10;
        i++;
      }
      assert(isPositive_ == rhs.isPositive_);
      res.isPositive_ = isPositive_;
      return res;
    }
  }
  void operator+=(const BigInt &rhs) { *this = *this + rhs; }
  BigInt operator+(const long long rhs) const { return BigInt{rhs} + *this; }
  void operator+=(const long long rhs) { *this += BigInt{rhs}; }

  // https://en.cppreference.com/w/cpp/language/operators
  BigInt operator-() const {
    BigInt res{*this};
    res.isPositive_ = !this->isPositive_;
    return res;
  }
  BigInt operator-(const BigInt &rhs) const {
    if (isPositive_ == true && rhs.isPositive_ == false) {
      // lhs(+) - rhs(-)
      return *this + (-rhs);
    } else if (isPositive_ == false && rhs.isPositive_ == true) {
      // lhs(-) - rhs(+)
      return -(-(*this) + rhs);
    } else if (isPositive_ == true && rhs.isPositive_ == true) {
      // lhs(+) - rhs(+)
      if (numVec_.size() > rhs.numVec_.size()) {
        return minusBasic(*this, rhs);
      } else if (numVec_.size() < rhs.numVec_.size()) {
        return -minusBasic(rhs, *this);
      } else {
        bool isMinusOf = false;
        for (size_t i = numVec_.size(); i > 0; i++) {
          if (numVec_[i - 1] == rhs.numVec_[i - 1]) continue;
          if (numVec_[i - 1] < rhs.numVec_[i - 1]) {
            isMinusOf = true;
            break;
          } else {
            isMinusOf = false;
            break;
          }
        }
        if (isMinusOf) {
          return -(rhs - *this);
        } else {
          return minusBasic(*this, rhs);
        }
      }
    } else {
      // lhs(-) - rhs(-)
      return -rhs - (-(*this));
    }
  }
  void operator-=(const BigInt &rhs) { *this = *this - rhs; }
  BigInt operator-(const long long rhs) const { return *this - BigInt{rhs}; }
  void operator-=(const long long rhs) { *this -= BigInt{rhs}; }

  BigInt operator*(const BigInt &rhs) const {
    if (*this == 0 || rhs == 0) return BigInt{0};
    BigInt res{true,
               std::vector<ElemType_t>(numVec_.size() + rhs.numVec_.size(), 0)};
    res.isPositive_ = res.isPositive_ && rhs.isPositive_;
    for (size_t i = 0; i < numVec_.size(); i++) {
      ElemType_t t = 0;
      for (size_t j = 0; j < rhs.numVec_.size(); j++) {
        t += (numVec_[i] * rhs.numVec_[j]);
        t += res.numVec_[i + j];
        res.numVec_[i + j] = (t % 10);
        t /= 10;
      }
      size_t tailIdx = 0;
      while (t > 0) {
        t += res.numVec_[i + rhs.numVec_.size() + tailIdx];
        res.numVec_[i + rhs.numVec_.size() + tailIdx] = t % 10;
        t /= 10;
        tailIdx++;
      }
    }
    res.removeTailZero();
    return res;
  }
  void operator*=(const BigInt &rhs) { *this = *this * rhs; }
  BigInt operator*(const long long rhs) const { return *this * BigInt{rhs}; }
  void operator*=(const long long rhs) { *this = *this * BigInt{rhs}; }

  friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs) {
    std::string str{};
    if (rhs.isPositive_ == false) {
      os << "-";
    }
    for (size_t i = rhs.numVec_.size(); i > 0; i--) {
      os << std::to_string(rhs.numVec_[i - 1]);
    }
    return os;
  }

  std::string to_string() const {
    std::string str{};
    if (isPositive_ == false) {
      str += "-";
    }
    for (size_t i = numVec_.size(); i > 0; i--) {
      str += std::to_string(numVec_[i - 1]);
    }
    return str;
  }

  bool isZero() const {
    if (numVec_.size() == 0 || (numVec_.size() == 1 && numVec_[0] == 0)) {
      return true;
    }
    return false;
  }

 private:
  explicit BigInt() : numVec_{}, isPositive_{true} {}
  explicit BigInt(const bool isPositive, const std::vector<ElemType_t> &numVec)
      : isPositive_{isPositive}, numVec_{numVec} {}

  void removeTailZero() {
    std::vector<ElemType_t> &vec = numVec_;
    while (vec.size() > 1 && vec[vec.size() - 1] == 0) {
      vec.pop_back();
    }
  }

  friend BigInt minusBasic(const BigInt &lhs, const BigInt &rhs) {
    // lhs(+) - rhs(+) and lhs > rhs
    assert(lhs > 0 && rhs > 0 && lhs >= rhs);
    BigInt res{};
    ElemType_t t = 0, u = 0;
    for (size_t i = 0; i < lhs.numVec_.size(); i++) {
      t = u;
      t += lhs.numVec_[i];
      if (i < rhs.numVec_.size()) {
        t -= rhs.numVec_[i];
      }
      if (t < 0) {
        t += 10;
        u = -1;
      } else {
        u = 0;
      }
      res.numVec_.push_back(t);
    }
    res.removeTailZero();
    return res;
  }

  std::vector<ElemType_t> numVec_;
  bool isPositive_;
};
}  // namespace utils
