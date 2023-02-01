#include "s21_matrix_oop.h"

void S21Matrix::Output() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void S21Matrix::Equals_(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Delit_() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::DeterminantAll_(S21Matrix &temp, double *res) {
  int n = temp.cols_;
  if (n == 1) {
    *res = temp(0, 0);
  } else if (n == 2) {
    *res = temp.matrix_[0][0] * temp.matrix_[1][1] -
           temp.matrix_[0][1] * temp.matrix_[1][0];
  } else {
    double main_diag = 1.;
    for (int i = 0; i < n; i++) main_diag = main_diag * temp.matrix_[i][i];
    if (main_diag != 0) {
      Decomp_(temp, res);
    } else {
      RecursiveDecomposition_(temp, res, n);
    }
  }
}

void S21Matrix::Decomp_(S21Matrix &temp, double *res) {
  int size_matrix = temp.cols_;
  S21Matrix L(size_matrix, size_matrix), U(size_matrix, size_matrix);
  *res = 1.;
  for (int i = 0; i < size_matrix; i++) {
    for (int j = 0; j < size_matrix; j++) {
      U.matrix_[0][i] = temp.matrix_[0][i];
      L.matrix_[i][0] = temp.matrix_[i][0] / U.matrix_[0][0];
      double sum = 0;
      for (int k = 0; k < i; k++) {
        sum += L.matrix_[i][k] * U.matrix_[k][j];
      }
      U.matrix_[i][j] = temp.matrix_[i][j] - sum;
      if (i > j) {
        L.matrix_[j][i] = 0;
      } else {
        sum = 0;
        for (int k = 0; k < i; k++) {
          sum += L.matrix_[j][k] * U.matrix_[k][i];
        }
        L.matrix_[j][i] = (temp.matrix_[j][i] - sum) / U.matrix_[i][i];
      }
    }
  }
  for (int i = 0; i < size_matrix; i++) {
    *res = *res * U.matrix_[i][i];
  }
}

void S21Matrix::RecursiveDecomposition_(S21Matrix &temp, double *res, int n) {
  S21Matrix temp_matrix(n - 1, n - 1);
  int sign = 1;
  for (int i = 0; i < n; i++) {
    SubMatrix_(temp, temp_matrix, 0, i);
    double temp_determ;
    DeterminantAll_(temp_matrix, &temp_determ);
    *res += sign * temp.matrix_[0][i] * temp_determ;
    sign = -sign;
  }
}

void S21Matrix::SubMatrix_(S21Matrix &temp, S21Matrix &temp_determ, int p,
                           int q) {
  int i = 0, j = 0;
  int n = temp.rows_;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (row != p && col != q) {
        temp_determ.matrix_[i][j++] = temp.matrix_[row][col];
        if (j == n - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

void S21Matrix::Minor_(int row, int column, double *minor) {
  int size_matrix = cols_;
  S21Matrix minor_matrix(size_matrix - 1, size_matrix - 1);
  int new_row, new_column;
  for (int i = 0; i < size_matrix - 1; i++) {
    if (i < row)
      new_row = i;
    else
      new_row = i + 1;
    for (int j = 0; j < size_matrix - 1; j++) {
      if (j < column)
        new_column = j;
      else
        new_column = j + 1;
      minor_matrix.matrix_[i][j] = matrix_[new_row][new_column];
    }
  }
  *minor = minor_matrix.Determinant();
}

void S21Matrix::FillMatrix() {
  double value = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
      value++;
    }
  }
}

void S21Matrix::SetValues(double *str) {
  int index = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (str[index]) {
        matrix_[i][j] = str[index];
      } else {
        matrix_[i][j] = index;
      }
      index++;
    }
  }
}

void S21Matrix::SetSize(int rows, int cols) {
  S21Matrix tmp(rows, cols);
  tmp.rows_ = rows;
  tmp.cols_ = cols;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_ && i < rows_) {
        tmp(i, j) = matrix_[i][j];
      } else {
        tmp(i, j) = 0;
      }
    }
  }
  *this = std::move(tmp);
}