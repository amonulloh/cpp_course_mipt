#include <algorithm>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() { matrix_ = std::vector<std::vector<T>>(N, std::vector<T>(M)); };

  Matrix(const Matrix& other) {
    matrix_ = std::vector<std::vector<T>>(N, std::vector<T>(M));
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] = other(i, j);
      }
    }
  }
  explicit Matrix(const std::vector<std::vector<T>>& other)
      : matrix_(std::move(other)) {}

  Matrix(const T& elem) {
    matrix_ = std::vector<std::vector<T>>(N, std::vector<T>(M, elem));
  }

  Matrix<N, M, T>& operator+=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
    return *this;
  }

  Matrix<N, M, T>& operator-=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
    return *this;
  }

  Matrix& operator*=(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] *= elem;
      }
    }
    return *this;
  }

  const T& operator()(size_t ind, size_t jnd) const {
    return matrix_[ind][jnd];
  }
  T& operator()(size_t ind, size_t jnd) { return matrix_[ind][jnd]; }

  Matrix<M, N, T> Transposed() {
    Matrix<M, N, T> dop;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        dop(j, i) = matrix_[i][j];
      }
    }
    return dop;
  }

  T Trace() {
    T temp = 0;
    for (size_t i = 0; i < std::max(N, M); ++i) {
      temp += matrix_[i][i];
    }
    return temp;
  }

  bool operator==(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::vector<T>> matrix_;
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& matrix, const T& num) {
  Matrix<N, M, T> dop(matrix);
  dop *= num;
  return dop;
}

template <size_t N0, size_t M0, size_t M1, typename T>
Matrix<N0, M1, T> operator*(const Matrix<N0, M0, T>& matrix1,
                            const Matrix<M0, M1, T>& matrix2) {
  Matrix<N0, M1, T> dop;
  size_t ind = 0;
  T temp = 0;
  for (size_t i = 0; i < N0; ++i) {
    size_t jnd = 0;
    for (size_t j = 0; j < M1; ++j) {
      for (size_t k = 0; k < M0; ++k) {
        temp += matrix1(i, k) * matrix2(k, j);
      }
      dop(ind, jnd) = temp;
      temp = 0;
      ++jnd;
    }
    ++ind;
  }
  return dop;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& matrix1,
                          const Matrix<N, M, T>& matrix2) {
  Matrix<N, M, T> dop(matrix1);
  dop += matrix2;
  return dop;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& matrix1,
                          const Matrix<N, M, T>& matrix2) {
  Matrix<N, M, T> dop(matrix1);
  dop -= matrix2;
  return dop;
}