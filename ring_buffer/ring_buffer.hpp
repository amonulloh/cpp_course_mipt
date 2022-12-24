#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity) {
    arr_ = std::vector<int>(capacity);
    cap_ = capacity;
  }

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (size_ < cap_) {
      end_ = (end_ + 1) % cap_;
      arr_[end_] = element;
      size_++;
    } else {
      return false;
    }
    return true;
  }

  bool TryPop(int* element) {
    if (size_ == 0) {
      return false;
    }
    size_--;
    *element = arr_[begin_];
    begin_ = (begin_ + 1) % cap_;
    return true;
  }

 private:
  std::vector<int> arr_;
  int begin_ = 0;
  int end_ = -1;
  size_t cap_;
  size_t size_ = 0;
};
