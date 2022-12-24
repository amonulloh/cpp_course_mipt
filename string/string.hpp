#pragma once

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

class String {
 public:
  void Cap();
  void ArrCap();
  String();
  String(size_t size, char character);
  String(const char* cstr);
  ~String();
  String(const String& cstr);
  String& operator=(const String& str);
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& operator[](size_t ind);
  const char& operator[](size_t ind) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;
  char* Data();
  String& operator+=(const String& str);
  String& operator*=(size_t n);
  bool Ravno(size_t i, const String& delim);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings);

 private:
  size_t capacity_;
  size_t size_;
  char* st_;
};

bool operator<(const String& str1, const String& str2);
bool operator==(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
String operator+(const String& str1, const String& str2);
String operator*(const String& str1, size_t n);
std::istream& operator>>(std::istream& is, String& str);
std::ostream& operator<<(std::ostream& is, const String& str);