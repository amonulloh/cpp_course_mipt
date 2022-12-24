#pragma once
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(std::string str);
  BigInt(int64_t);
  BigInt(const BigInt&);
  ~BigInt();
  BigInt& operator=(int64_t);
  BigInt& operator=(const BigInt&);
  bool Sign() const;
  std::vector<int64_t>& Data();
  std::vector<int64_t> Data() const;
  size_t Size() const;

  friend BigInt operator+(const BigInt&, const BigInt&);
  friend BigInt operator-(const BigInt&, const BigInt&);
  friend BigInt operator*(const BigInt&, const BigInt&);
  friend BigInt operator/(const BigInt&, const BigInt&);
  friend BigInt operator%(const BigInt&, const BigInt&);

  friend bool operator<(const BigInt&, const BigInt&);
  friend bool operator>(const BigInt&, const BigInt&);
  friend bool operator==(const BigInt&, const BigInt&);
  friend bool operator!=(const BigInt&, const BigInt&);
  friend bool operator>=(const BigInt&, const BigInt&);
  friend bool operator<=(const BigInt&, const BigInt&);

  void Repl(BigInt& num2);
  void RemoveZeros();
  BigInt operator++(int);
  BigInt& operator++();
  BigInt operator--(int);
  BigInt& operator--();
  BigInt operator-();
  BigInt& operator+=(const BigInt&);
  void CompSub(BigInt&);
  BigInt& operator-=(const BigInt&);
  void CompMult(const BigInt&, BigInt&, int64_t&, size_t&);
  BigInt& operator*=(const BigInt&);
  BigInt operator/=(const BigInt&);
  BigInt& operator%=(const BigInt&);

 private:
  bool isnegative_ = false;
  std::vector<int64_t> digit_;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
bool Compare(const BigInt&, const BigInt&);
bool Compare2(const BigInt&, const BigInt&);
bool operator<(const BigInt&, const BigInt&);
bool operator==(const BigInt&, const BigInt&);
bool operator>(const BigInt&, const BigInt&);
bool operator!=(const BigInt&, const BigInt&);
bool operator<=(const BigInt&, const BigInt&);
bool operator>=(const BigInt&, const BigInt&);
std::istream& operator>>(std::istream&, BigInt&);
std::ostream& operator<<(std::ostream&, const BigInt&);
