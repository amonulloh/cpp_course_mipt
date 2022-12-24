#include "big_integer.hpp"

const int64_t kNine = 9;
const int64_t kTen = 10;

BigInt::BigInt() = default;

BigInt::BigInt(std::string str) {
  if (str.length() == 0) {
    isnegative_ = false;
  } else {
    uint64_t ind = 0;
    if (str[0] == '-') {
      isnegative_ = true;
      if (str.size() == 2 && str[1] == '0') {
        isnegative_ = false;
      }
      ++ind;
    } else {
      isnegative_ = false;
    }
    while (ind < str.size()) {
      digit_.push_back(str[ind] - '0');
      ++ind;
    }
  }
}

BigInt::BigInt(int64_t number) {
  if (number == 0) {
    isnegative_ = false;
    digit_.push_back(0);
  } else {
    if (number > 0) {
      isnegative_ = false;
    } else {
      isnegative_ = true;
      if (number == std::numeric_limits<int64_t>::min()) {
        digit_.insert(digit_.begin(), llabs(number % kTen));
        number /= kTen;
      }
      number *= -1;
    }
    while (number > 0) {
      digit_.insert(digit_.begin(), number % kTen);
      number /= kTen;
    }
  }
}

BigInt::BigInt(const BigInt& number) {
  if (digit_ != number.digit_) {
    digit_.clear();
    for (size_t i = 0; i < number.Size(); ++i) {
      digit_.push_back(number.digit_[i]);
    }
  }
}

BigInt& BigInt::operator=(int64_t num2) {
  if (num2 == 0) {
    isnegative_ = false;
    digit_.push_back(0);
    return *this;
  }
  if (num2 > 0) {
    isnegative_ = false;
  } else {
    isnegative_ = true;
    num2 *= -1;
  }
  while (num2 > 0) {
    digit_.insert(digit_.begin(), num2 % kTen);
    num2 /= kTen;
  }
  return *this;
}

BigInt& BigInt::operator=(const BigInt& num2) {
  if (*this != num2) {
    digit_.clear();
    isnegative_ = num2.isnegative_;
    for (int64_t ind : num2.digit_) {
      digit_.push_back(ind);
    }
  }
  return *this;
}

BigInt::~BigInt() { digit_.clear(); }

bool BigInt::Sign() const { return isnegative_; }

std::vector<int64_t>& BigInt::Data() { return digit_; }

std::vector<int64_t> BigInt::Data() const { return digit_; }

size_t BigInt::Size() const { return digit_.size(); }

void BigInt::Repl(BigInt& num2) {
  size_t max_size;
  if (num2.digit_.size() > digit_.size()) {
    max_size = num2.digit_.size();
    while (max_size != digit_.size()) {
      digit_.insert(digit_.begin(), 0);
    }
  } else {
    max_size = digit_.size();
    while (num2.digit_.size() != max_size) {
      num2.digit_.insert(num2.digit_.begin(), 0);
    }
  }
}

void BigInt::RemoveZeros() {
  while (digit_[0] == 0 && digit_.size() != 1) {
    digit_.erase(digit_.begin());
  }
  if (isnegative_ && digit_.size() == 1 && digit_[0] == 0) {
    isnegative_ = false;
  }
}

BigInt BigInt::operator++(int) {
  BigInt res = *this;
  *this += 1;
  return res;
}

BigInt& BigInt::operator++() { return *this += 1; }

BigInt BigInt::operator--(int) {
  BigInt res = *this;
  *this -= 1;
  RemoveZeros();
  return res;
}

BigInt& BigInt::operator--() {
  *this -= 1;
  RemoveZeros();
  return *this;
}

BigInt BigInt::operator-() {
  BigInt copy = *this;
  if (copy != 0) {
    copy.isnegative_ = !isnegative_;
  }
  return copy;
}

BigInt& BigInt::operator+=(const BigInt& num2) {
  BigInt num = num2;
  if (isnegative_ ^ num2.isnegative_) {
    if (isnegative_) {
      isnegative_ = false;
      num -= *this;
      return *this = num;
    }
    num.isnegative_ = false;
    return *this -= num;
  }
  int64_t carry = 0;
  Repl(num);
  for (size_t i = digit_.size(); i > 0; --i) {
    digit_[i - 1] += carry + num.digit_[i - 1];
    if (digit_[i - 1] > kNine) {
      carry = 1;
      digit_[i - 1] %= kTen;
    } else {
      carry = 0;
    }
  }
  if (carry == 1) {
    digit_.insert(digit_.begin(), carry);
  }
  return *this;
}

void BigInt::CompSub(BigInt& num) {
  int64_t carry = 0;
  for (size_t i = digit_.size(); i > 0; --i) {
    digit_[i - 1] -= carry;
    if (digit_[i - 1] < num.digit_[i - 1]) {
      carry = 1;
      digit_[i - 1] += kTen;
    } else {
      carry = 0;
    }
    digit_[i - 1] = digit_[i - 1] - num.digit_[i - 1];
  }
}

BigInt& BigInt::operator-=(const BigInt& num2) {
  BigInt num = num2;
  if (isnegative_ ^ num2.isnegative_) {
    if (isnegative_) {
      isnegative_ = false;
      *this += num2;
      isnegative_ = true;
      return *this;
    }
    num.isnegative_ = false;
    return *this += num;
  }
  if (isnegative_) {
    num.isnegative_ = false;
    return *this += num;
  }
  Repl(num);
  if (*this == num) {
    digit_.clear();
    digit_.push_back(0);
  } else {
    if (*this > num) {
      CompSub(num);
    } else {
      *this = num - *this;
      isnegative_ = true;
    }
    RemoveZeros();
  }
  return *this;
}

void BigInt::CompMult(const BigInt& num2, BigInt& res, int64_t& carry,
                      size_t& ind) {
  for (size_t j = digit_.size(); j > 0; --j) {
    res.digit_[j - 1] = num2.digit_[ind] * digit_[j - 1] + carry;
    if (res.digit_[j - 1] > kNine) {
      carry = (res.digit_[j - 1] - res.digit_[j - 1] % kTen) / kTen;
      res.digit_[j - 1] %= kTen;
    } else {
      carry = 0;
    }
  }
}

BigInt& BigInt::operator*=(const BigInt& num2) {
  BigInt res = *this;
  res.isnegative_ = false;
  std::fill(res.digit_.begin(), res.digit_.end(), 0);
  BigInt tmp = 0;
  int64_t carry = 0;
  bool flag = false;
  if (isnegative_ ^ num2.isnegative_) {
    flag = true;
  }
  isnegative_ = false;
  for (size_t i = 0; i < num2.Size(); ++i) {
    CompMult(num2, res, carry, i);
    if (carry > 0) {
      res.digit_.insert(res.digit_.begin(), carry);
      carry = 0;
    }
    tmp.digit_.push_back(0);
    tmp += res;
    if (res.Size() > this->Size()) {
      res.digit_.pop_back();
    }
    std::fill(res.digit_.begin(), res.digit_.end(), 0);
  }
  *this = tmp;
  isnegative_ = flag;
  RemoveZeros();
  return *this;
}

BigInt BigInt::operator/=(const BigInt& num2) {
  bool flag = false;
  if (isnegative_ ^ num2.isnegative_) {
    flag = true;
  }
  BigInt num = num2;
  num.isnegative_ = false;
  isnegative_ = false;
  BigInt tmp = *this;
  BigInt res = *this;
  for (size_t j = 0; j < tmp.Size(); ++j) {
    tmp.digit_[j] = kNine;
  }
  for (size_t i = 0; i < digit_.size(); ++i) {
    while (((tmp * num) >= res) && (tmp.digit_[i] != 0)) {
      --tmp.digit_[i];
    }
    if (((tmp * num) > res) && (tmp.digit_[i] == 0)) {
      continue;
    }
    ++tmp.digit_[i];
  }
  if ((tmp * num) != res) {
    --tmp.digit_.back();
  }
  *this = tmp;
  isnegative_ = flag;
  RemoveZeros();
  return *this;
}

BigInt& BigInt::operator%=(const BigInt& num2) {
  *this = *this - num2 * (*this / num2);
  return *this;
}

BigInt operator+(const BigInt& num1, const BigInt& num2) {
  BigInt tmp;
  tmp = num1;
  tmp += num2;
  return tmp;
}

BigInt operator-(const BigInt& num1, const BigInt& num2) {
  BigInt tmp;
  tmp = num1;
  tmp -= num2;
  return tmp;
}

BigInt operator*(const BigInt& num1, const BigInt& num2) {
  BigInt tmp;
  tmp = num1;
  tmp *= num2;
  return tmp;
}

BigInt operator/(const BigInt& num1, const BigInt& num2) {
  BigInt tmp;
  tmp = num1;
  tmp /= num2;
  return tmp;
}

BigInt operator%(const BigInt& num1, const BigInt& num2) {
  BigInt tmp;
  tmp = num1;
  tmp %= num2;
  return tmp;
}

bool Compare(const BigInt& num1, const BigInt& num2) {
  if (num1.Size() == num2.Size()) {
    for (size_t i = 0; i < num1.Size(); ++i) {
      if (num1.Data()[i] == num2.Data()[i]) {
        continue;
      }
      return (num1.Data()[i] < num2.Data()[i]);
    }
  }
  return (num1.Size() < num2.Size());
}

bool Compare2(const BigInt& num1, const BigInt& num2) {
  if (num1.Size() == num2.Size()) {
    for (size_t i = 0; i < num1.Size(); ++i) {
      if (num1.Data()[i] == num2.Data()[i]) {
        continue;
      }
      return (num2.Data()[i] < num1.Data()[i]);
    }
  }
  return (num2.Size() < num1.Size());
}

bool operator<(const BigInt& num1, const BigInt& num2) {
  if (num1.Sign() ^ num2.Sign()) {
    return (num1.Sign());
  }
  if (num1.Sign()) {
    return Compare2(num1, num2);
  }
  return Compare(num1, num2);
}

bool operator==(const BigInt& num1, const BigInt& num2) {
  return !(num1 < num2 || num2 < num1);
}

bool operator>(const BigInt& num1, const BigInt& num2) {
  return !(num1 < num2 || num1 == num2);
}

bool operator!=(const BigInt& num1, const BigInt& num2) {
  return !(num1 == num2);
}

bool operator>=(const BigInt& num1, const BigInt& num2) {
  return ((num1 > num2) || (num1 == num2));
}

bool operator<=(const BigInt& num1, const BigInt& num2) {
  return ((num1 < num2) || (num1 == num2));
}

std::istream& operator>>(std::istream& icin, BigInt& num) {
  std::string input;
  icin >> input;
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] == '\'') {
      input.erase(input.begin() + i);
    }
  }
  num = BigInt(input);
  return icin;
}

std::ostream& operator<<(std::ostream& icout, const BigInt& number) {
  BigInt num = number;
  if (number.Sign()) {
    num.Data()[0] = num.Data()[0] * -1;
  }
  for (int64_t idx : num.Data()) {
    icout << idx;
  }
  return icout;
}
