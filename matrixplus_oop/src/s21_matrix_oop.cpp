#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) { ; }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::out_of_range("Столбцы и строки матрицы не могут быть меньше 1");
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  Equals_(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { Delit_(); }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool bool_target = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) bool_target = false;
  for (int i = 0; i < other.rows_ && bool_target; i++) {
    for (int j = 0; j < other.cols_ && bool_target; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) bool_target = false;
    }
  }
  return bool_target;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Столбцы и строки матриц должны быть равны");
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Столбцы и строки матриц должны быть равны");
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::out_of_range(
        "Количество столбцов должно совподать с\
                                количеством строк входной матрицы");
  S21Matrix res_matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      for (int aga = 0; aga < other.cols_; aga++) {
        res_matrix.matrix_[i][j] += matrix_[i][aga] * other.matrix_[aga][j];
      }
    }
  }
  *this = std::move(res_matrix);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::out_of_range("Матрица должна быть квадратной");
  int size_matrix = cols_;
  S21Matrix res(size_matrix, size_matrix);
  for (int i = 0; i < size_matrix; i++) {
    for (int j = 0; j < size_matrix; j++) {
      Minor_(i, j, &res.matrix_[i][j]);
      res.matrix_[i][j] = res.matrix_[i][j] * pow(-1.0, i + j);
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::out_of_range("Матрица должна быть квадратной");
  double res = 0;
  S21Matrix tmp(*this);
  DeterminantAll_(tmp, &res);
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determ = Determinant();
  if (fabs(determ) < 1e-7)
    throw std::out_of_range("Определитель матрицы не может быть равен 0");
  S21Matrix res = CalcComplements().Transpose();
  res.MulNumber(1.0 / determ);
  return res;
}
