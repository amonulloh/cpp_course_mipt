#pragma once

int* LowerBound(int* first, int* last, int value) {
  int* left = first;
  int* right = last;
  if (value <= *left) {
    return first;
  }
  if (value > *(right - 1)) {
    return last;
  }
  while (left + 1 < right) {
    int* middle = ((right - left) / 2) + left;
    if (*middle == value) {
      return middle;
    }
    if (*middle < value) {
      left = middle;
    }
    if (*middle > value) {
      right = middle;
    }
  }
  return right;
}
