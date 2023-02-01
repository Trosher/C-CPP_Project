#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  // Сравнение
  void Equals_(const S21Matrix &other);
  // Очистка
  void Delit_();
  // Функция проведения оперции вычисления детерминанта
  void DeterminantAll_(S21Matrix &temp, double *res);
  // Вычисление детирминанта по диогонали
  void Decomp_(S21Matrix &temp, double *res);
  // Вычисление детирминанта через рекурсивное разложение
  void RecursiveDecomposition_(S21Matrix &temp, double *res, int n);
  // Удаление столбца матрицы
  void SubMatrix_(S21Matrix &temp, S21Matrix &temp_determ, int p, int q);
  // Расщет минора матрицы
  void Minor_(int row, int column, double *minor);

 public:
  // Методы
  /*
      Базовый конструктор, инициализирующий матрицу некоторой заранее заданной
     размерностью
  */
  S21Matrix();
  /*
      Параметризированный конструктор с количеством строк и столбцов
  */
  S21Matrix(int rows, int cols);
  /*
      Конструктор копирования
  */
  S21Matrix(const S21Matrix &other);
  /*
      Конструктор переноса
  */
  S21Matrix(S21Matrix &&other);
  /*
      Деструктор
  */
  ~S21Matrix();

  // Бинарные математические опeрации над матрицами
  /*
      EqMatrix - Проверяет матрицы на равенство между собой
  */
  bool EqMatrix(const S21Matrix &other);
  /*
      SumMatrix - Прибавляет вторую матрицу к текущей
      Исключения - различная размерность матриц
  */
  void SumMatrix(const S21Matrix &other);
  /*
      SubMatrix - Вычитает из текущей матрицы другую
      Исключения - различная размерность матриц
  */
  void SubMatrix(const S21Matrix &other);
  /*
      MulNumber - Умножает текущую матрицу на число
  */
  void MulNumber(const double num);
  /*
      MulMatrix - Умножает текущую матрицу на вторую матрицу
      Исключения - Число столбцов первой матрицы не равно числу строк второй
     матрицы
  */
  void MulMatrix(const S21Matrix &other);

  // Унарные математические опeрации над матрицами
  /*
      Transpose - Создает новую транспонированную матрицу из текущей и
     возвращает ее
  */
  S21Matrix Transpose();
  /*
      CalcComplements - Вычисляет матрицу алгебраических дополнений
                      текущей матрицы и возвращает ее
      Исключения - Матрица не является квадратной
  */
  S21Matrix CalcComplements();
  /*
      Determinant - Вычисляет и возвращает определитель текущей матрицы
      Исключения - Матрица не является квадратной
  */
  double Determinant();
  /*
      InverseMatrix - Вычисляет и возвращает обратную матрицу
      Исключения - Определитель матрицы равен 0
  */
  S21Matrix InverseMatrix();

  // Перегрузка операторов

  /*
      Перегрузка оператора =
  */
  const S21Matrix &operator=(const S21Matrix &other) {
    S21Matrix tmp(other);
    if (matrix_ != nullptr) Delit_();
    *this = std::move(tmp);
    return other;
  }
  S21Matrix &operator=(S21Matrix &&other) {
    if (matrix_ != nullptr) Delit_();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
    return *this;
  }
  /*
      Перегрузка оператора +=
  */
  void operator+=(const S21Matrix &other) { SumMatrix(other); }
  /*
      Перегрузка оператора -=
  */
  void operator-=(const S21Matrix &other) { SubMatrix(other); }
  /*
      Перегрузка оператора *=
  */
  void operator*=(const S21Matrix &other) { MulMatrix(other); }
  void operator*=(double other) { MulNumber(other); }
  /*
      Перегрузка оператора ==
  */
  bool operator==(const S21Matrix &other) { return EqMatrix(other); }
  /*
      Перегрузка оператора -
  */
  S21Matrix operator-(const S21Matrix &other) {
    S21Matrix res(*this);
    res.SubMatrix(other);
    return res;
  }
  /*
      Перегрузка оператора +
  */
  S21Matrix operator+(const S21Matrix &other) {
    S21Matrix res(*this);
    res.SumMatrix(other);
    return res;
  }
  /*
      Перегрузка оператора *
  */
  S21Matrix operator*(const S21Matrix &other) {
    S21Matrix res(*this);
    res.MulMatrix(other);
    return res;
  }
  S21Matrix operator*(double other) {
    S21Matrix res(*this);
    res.MulNumber(other);
    return res;
  }
  /*
      Перегрузка для индексации
  */
  double &operator()(int i, int j) {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
      throw std::out_of_range("Выход за пределы матрицы");
    return matrix_[i][j];
  }

  // Гетеры и сеторы

  // Получить значения переменной rows_
  int GetRows() { return rows_; }

  // Получить значения переменной cols_
  int GetCols() { return cols_; }

  // Устоновить значения переменной rows_
  void SetRows(int NewRows) {
    if (NewRows < 1) {
      throw std::out_of_range("Значения rows_ не могут быть меньше 1");
    }
    if (rows_ != NewRows) {
      SetSize(NewRows, cols_);
    }
  }

  // Устоновить значения переменной cols_
  void SetCols(int NewCols) {
    if (NewCols < 1)
        throw std::out_of_range("Значения cols_ не могут быть меньше 1");
    if (cols_ != NewCols) {
        SetSize(rows_, NewCols);
    }
  }

  // Методы заполнения матрицы
  /*
      Заполнение матрицы от 1
  */
  void FillMatrix();
  /*
      Заполнение матрицы значениями вектора
  */
  void SetValues(double *str);

  // Метод изменения размера матрицы
  void SetSize(int i, int j);

  // Метод отображения матрицы
  void Output();
};

#endif  // SRC_S21_MATRIX_OOP_H_