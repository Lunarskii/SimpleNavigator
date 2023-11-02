#ifndef A2_SIMPLENAVIGATOR_INCLUDE_MATRIX_MATRIX_H_
#define A2_SIMPLENAVIGATOR_INCLUDE_MATRIX_MATRIX_H_

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace s21 {

template <class T>
class Matrix {
 public:
  using i_type = std::size_t;
  using base = std::vector<T>;
  inline static double fp_compare_precision = 1e-6;

  Matrix() = default;
  explicit Matrix(i_type size, T value = T());
  Matrix(i_type size, const base& data);
  Matrix(i_type size, base&& data);

  T& operator()(i_type row, i_type col);
  const T& operator()(i_type row, i_type col) const;

  [[nodiscard]] i_type GetSize() const;
  i_type GetSize();

  struct ReadRow;
  struct WriteRow;
  WriteRow operator[](i_type row);
  ReadRow operator[](i_type row) const;

  bool operator==(const Matrix& other) const;
  bool operator!=(const Matrix& other) const;

  void Print(std::ostream& os = std::cout) const;
  void PrintFull(std::ostream& os = std::cout) const;
  void ReadFull(std::istream& is = std::cin);

 private:
  i_type rows_{};
  i_type cols_{};
  base data_;
};

template <class T>
Matrix<T>::Matrix(i_type size, T value)
    : rows_(size), cols_(size), data_(size * size, value) {}

template <class T>
Matrix<T>::Matrix(i_type size, const base& data)
    : rows_(size), cols_(size), data_(data) {}

template <class T>
Matrix<T>::Matrix(i_type size, base&& data)
    : rows_(size), cols_(size), data_(data) {}

template <class T>
struct Matrix<T>::ReadRow {
  const Matrix& m_;
  i_type row_;

  ReadRow(const Matrix& matrix, i_type row) : m_(matrix), row_(row) {}

  const T& operator[](i_type col) const { return m_(row_, col); }
};

template <class T>
struct Matrix<T>::WriteRow {
  Matrix& m_;
  i_type row_;

  WriteRow(Matrix& matrix, i_type row) : m_(matrix), row_(row) {}

  T& operator[](i_type col) { return m_(row_, col); }
};

template <class T>
typename Matrix<T>::WriteRow Matrix<T>::operator[](i_type row) {
  return WriteRow(*this, row);
}

template <class T>
typename Matrix<T>::ReadRow Matrix<T>::operator[](i_type row) const {
  return ReadRow(*this, row);
}

template <class T>
T& Matrix<T>::operator()(i_type row, i_type col) {
  return data_[row * cols_ + col];
}

template <class T>
const T& Matrix<T>::operator()(i_type row, i_type col) const {
  return data_[row * cols_ + col];
}

template <class T>
bool Matrix<T>::operator==(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  if constexpr (std::is_floating_point_v<T>) {
    for (i_type i = 0; i < rows_; ++i) {
      for (i_type j = 0; j < cols_; ++j) {
        if (std::abs(data_[cols_ * i + j] - other.data_[cols_ * i + j]) >
            fp_compare_precision) {
          return false;
        }
      }
    }
  } else {
    for (i_type i = 0; i < rows_; ++i) {
      for (i_type j = 0; j < cols_; ++j) {
        if (data_[cols_ * i + j] != other.data_[cols_ * i + j]) {
          return false;
        }
      }
    }
  }
  return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix& other) const {
  return *this != other;
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetSize() {
  return rows_;
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetSize() const {
  return rows_;
}

template <class T>
void Matrix<T>::Print(std::ostream& os) const {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      os << data_[i * cols_ + j] << '\t';
    }
    os << '\n';
  }
}

template <class T>
void Matrix<T>::PrintFull(std::ostream& os) const {
  os << rows_ << '\t' << cols_ << '\n';
  Print(os);
}

template <class T>
void Matrix<T>::ReadFull(std::istream& is) {
  rows_ = T();
  cols_ = T();
  data_.clear();
  std::string line;
  i_type num = 0;

  is >> std::skipws;
  if (is >> rows_) {
    cols_ = rows_;
  } else {
    throw std::invalid_argument("Incorrect data format");
  }
  while (std::getline(is, line)) {
    std::istringstream iss(line);

    for (i_type j = 0; j < cols_ && iss >> num; ++j) {
      if (data_.size() / cols_ != j && num == 0) {
        data_.push_back(std::numeric_limits<i_type>::max());
      } else {
        data_.push_back(num);
      }
    }

    if (data_.size() % cols_ != 0 || data_.size() > rows_ * cols_ ||
        !iss.eof()) {
      throw std::invalid_argument("Incorrect data format");
    }
  }
  if (data_.size() < rows_ * cols_) {
    throw std::invalid_argument("Incorrect data format");
  }
}

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_INCLUDE_MATRIX_MATRIX_H_
