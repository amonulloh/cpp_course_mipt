#include "string.hpp"

void String::Cap() {
  if (capacity_ == 0) {
    ++capacity_;
  }
  if (size_ >= capacity_) {
    capacity_ *= 2;
  }
}

void String::ArrCap() {
  char* dop = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    dop[i] = st_[i];
  }
  delete[] st_;
  st_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    st_[i] = dop[i];
  }
  st_[size_] = '\0';
  delete[] dop;
}

String::String() {
  size_ = 0;
  capacity_ = 0;
  st_ = nullptr;
}

String::String(size_t size, char character) {
  capacity_ = size;
  size_ = size;
  st_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size; ++i) {
    st_[i] = character;
  }
  st_[size_] = '\0';
}

String::String(const char* cstr) {
  size_t len = strlen(cstr);
  capacity_ = len;
  size_ = len;
  st_ = new char[capacity_ + 1];
  for (size_t i = 0; i < len; ++i) {
    st_[i] = cstr[i];
  }
  st_[size_] = '\0';
}

String::~String() { delete[] st_; }

String::String(const String& cstr) {
  size_ = cstr.size_;
  capacity_ = cstr.capacity_;
  st_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    st_[i] = cstr.st_[i];
  }
  st_[size_] = '\0';
}

String& String::operator=(const String& str) {
  if (&str != this) {
    delete[] st_;
    size_ = str.size_;
    capacity_ = str.capacity_;
    st_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      st_[i] = str.st_[i];
    }
    st_[size_] = '\0';
  }
  return *this;
}

void String::Clear() {
  if (st_ != nullptr) {
    st_[0] = '\0';
  }
  size_ = 0;
}

void String::PushBack(char character) {
  if (capacity_ == 0) {
    ++capacity_;
    st_ = new char[capacity_ + 1];
  }
  Cap();
  ArrCap();
  st_[size_++] = character;
  st_[size_] = '\0';
}

void String::PopBack() {
  if (size_ != 0) {
    st_[size_ - 1] = '\0';
    --size_;
  }
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    capacity_ = new_size;
    ArrCap();
  }
  size_ = new_size;
  st_[size_] = '\0';
}

void String::Resize(size_t new_size, char character) {
  if (new_size > capacity_) {
    capacity_ = new_size;
    ArrCap();
  }
  if (new_size > size_) {
    for (size_t i = size_; i < new_size; ++i) {
      st_[i] = character;
    }
  }
  size_ = new_size;
  st_[size_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    capacity_ = new_cap;
    ArrCap();
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    ArrCap();
  }
}

void String::Swap(String& other) {
  std::swap(st_, other.st_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

char& String::operator[](size_t ind) { return st_[ind]; }

const char& String::operator[](size_t ind) const { return st_[ind]; }

char& String::Front() { return st_[0]; }

const char& String::Front() const { return st_[0]; }

char& String::Back() { return st_[size_ - 1]; }

const char& String::Back() const { return st_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

char* String::Data() { return st_; }

const char* String::Data() const { return st_; }

String& String::operator+=(const String& str) {
  size_t sz = size_;
  capacity_ += str.capacity_;
  ArrCap();
  size_ += str.size_;
  for (size_t i = 0; i < str.size_; ++i) {
    st_[sz + i] = str.st_[i];
  }
  st_[size_] = '\0';
  return *this;
}

String& String::operator*=(size_t n) {
  size_t sz = size_;
  Reserve(size_ * n);
  size_ *= n;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < sz; ++j) {
      st_[sz * i + j] = st_[j];
    }
  }
  st_[size_] = '\0';
  return *this;
}

bool String::Ravno(size_t i, const String& delim) {
  for (size_t j = 0; j < delim.Size(); ++j) {
    if (st_[i] != delim[j]) {
      return false;
    }
    ++i;
  }
  return true;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> tmp;
  size_t begin = 0;
  size_t i = 0;
  String arr;
  while (i < size_ || st_[i] == delim[0]) {
    if (Ravno(i, delim)) {
      for (size_t k = begin; k < i; ++k) {
        arr.PushBack(st_[k]);
      }
      tmp.push_back(arr);
      begin = i + delim.size_;
      arr.Clear();
    }
    ++i;
  }
  for (size_t k = begin; k < size_; ++k) {
    arr.PushBack(st_[k]);
  }
  tmp.push_back(arr);
  return tmp;
}

String String::Join(const std::vector<String>& strings) {
  String tmp("");
  if (strings.empty()) {
    return tmp;
  }
  String dop2(st_);
  for (size_t i = 0; i < strings.size() - 1; ++i) {
    String dop1(strings[i].st_);
    tmp += dop1;
    tmp += dop2;
  }
  String dop1(strings.back().st_);
  tmp += dop1;
  tmp[tmp.size_] = '\0';
  return tmp;
}

bool operator<(const String& str1, const String& str2) {
  size_t min_size = std::min(str1.Size(), str2.Size());
  for (size_t i = 0; i < min_size; ++i) {
    if (str1.Data()[i] < str2.Data()[i]) {
      return true;
    }
  }
  return (str1.Size() < str2.Size());
}

bool operator==(const String& str1, const String& str2) {
  return !(str1 < str2 || str2 < str1);
}

bool operator>(const String& str1, const String& str2) {
  return !(str1 < str2 || str1 == str2);
}

bool operator!=(const String& str1, const String& str2) {
  return !(str1 == str2);
}

bool operator>=(const String& str1, const String& str2) {
  return ((str1 > str2) || (str1 == str2));
}

bool operator<=(const String& str1, const String& str2) {
  return ((str1 < str2) || (str1 == str2));
}

String operator+(const String& str1, const String& str2) {
  String tmp = str1;
  tmp += str2;
  return tmp;
}

String operator*(const String& str1, size_t n) {
  String tmp = str1;
  tmp *= n;
  return tmp;
}

std::istream& operator>>(std::istream& is, String& str) {
  char buf;
  while (is.get(buf) && (isspace(buf) == 0)) {
    str.PushBack(buf);
  }
  return is;
}

std::ostream& operator<<(std::ostream& is, const String& str) {
  is << str.Data();
  return is;
}