#include <gtest/gtest.h>

#include <climits>

#include "s21_matrix_oop.h"

TEST(matrix_test, SetCols1) {
  S21Matrix mtrx1(3, 3);
  try {
    mtrx1.SetCols(-1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Значения cols_ не могут быть меньше 1"));
  }
}

TEST(matrix_test, SetCols_and_GetCols) {
  S21Matrix mtrx1(3, 3);
  mtrx1.SetCols(1);
  ASSERT_EQ(mtrx1.GetCols(), 1);
}

TEST(matrix_test, SetRows1) {
  S21Matrix mtrx1(3, 3);
  try {
    mtrx1.SetRows(-1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Значения rows_ не могут быть меньше 1"));
  }
}

TEST(matrix_test, SetRows_and_GetRows) {
  S21Matrix mtrx1(3, 3);
  mtrx1.SetRows(1);
  ASSERT_EQ(mtrx1.GetRows(), 1);
}

TEST(matrix_test, oper_brackets1) {
  S21Matrix mtrx1(3, 3);
  try {
    mtrx1(-1, 4);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Выход за пределы матрицы"));
  }
}

TEST(matrix_test, oper_brackets2) {
  S21Matrix mtrx1(3, 3);
  double aga = mtrx1(2, 2);
  ASSERT_EQ(aga, 0);
}

TEST(matrix_test, oper_eq1) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(2, 2);
  ASSERT_EQ(false, mtrx1 == mtrx2);
}

TEST(matrix_test, oper_eq2) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(3, 3);
  ASSERT_EQ(true, mtrx1 == mtrx2);
}

TEST(matrix_test, sum1) {
  double nums_array[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(3, 3);
  mtrx1.FillMatrix();
  mtrx2.FillMatrix();
  S21Matrix mtrx3(3, 3);
  mtrx3.SetValues(nums_array);
  S21Matrix mtrx4 = mtrx1 + mtrx2;
  for (int i = 0; i < mtrx1.GetRows(); i++)
    for (int j = 0; j < mtrx1.GetCols(); j++)
      ASSERT_DOUBLE_EQ(mtrx3(i, j), mtrx4(i, j));
}

TEST(matrix_test, sum2) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(2, 3);
  try {
    S21Matrix mtrx3 = mtrx1 + mtrx2;
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(),
              std::string("Столбцы и строки матриц должны быть равны"));
  }
}

TEST(matrix_test, sub1) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(3, 3);
  mtrx1.FillMatrix();
  mtrx2.FillMatrix();
  S21Matrix mtrx3(3, 3);
  S21Matrix mtrx4 = mtrx1 - mtrx2;
  for (int i = 0; i < mtrx1.GetRows(); i++)
    for (int j = 0; j < mtrx1.GetCols(); j++)
      ASSERT_DOUBLE_EQ(mtrx3(i, j), mtrx4(i, j));
}

TEST(matrix_test, sub2) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(2, 3);
  try {
    S21Matrix mtrx3 = mtrx1 - mtrx2;
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(),
              std::string("Столбцы и строки матриц должны быть равны"));
  }
}

TEST(matrix_test, mul1) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(3, 3);
  double nums_array[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
  mtrx1.FillMatrix();
  mtrx2.FillMatrix();
  S21Matrix mtrx3(3, 3);
  mtrx3.SetValues(nums_array);
  S21Matrix mtrx4 = mtrx1 * mtrx2;
  for (int i = 0; i < mtrx1.GetRows(); i++)
    for (int j = 0; j < mtrx1.GetCols(); j++)
      ASSERT_DOUBLE_EQ(mtrx3(i, j), mtrx4(i, j));
}

TEST(matrix_test, mul2) {
  S21Matrix mtrx1(3, 3);
  double nums_array[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  mtrx1.FillMatrix();
  mtrx1 *= 2;
  int k = 0;
  for (int i = 0; i < mtrx1.GetRows(); i++)
    for (int j = 0; j < mtrx1.GetCols(); j++)
      ASSERT_DOUBLE_EQ(mtrx1(i, j), nums_array[k++]);
}

TEST(matrix_test, mul3) {
  S21Matrix mtrx1(3, 5);
  S21Matrix mtrx2(1, 3);
  try {
    S21Matrix mtrx3 = mtrx1 * mtrx2;
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Количество столбцов должно совподать с\
                                количеством строк входной матрицы"));
  }
}

TEST(matrix_test, construct1) {
  try {
    S21Matrix mtrx1(-1, 3);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(),
              std::string("Столбцы и строки матрицы не могут быть меньше 1"));
  }
}

TEST(matrix_test, construct2) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2;
  mtrx2 = mtrx1;
  S21Matrix matrx3;
  mtrx1.FillMatrix();
  mtrx2.FillMatrix();
  matrx3 = mtrx1 + mtrx2;
  // no errors, leaks
}

TEST(matrix_test, construct3) {
  S21Matrix a(3, 3);
  S21Matrix b(std::move(a));
  EXPECT_THROW(a(1, 1) = 1, std::out_of_range);
  // no errors, leaks
}

TEST(matrix_test, eq1) {
  S21Matrix mtrx1(3, 5);
  S21Matrix mtrx2(1, 3);
  ASSERT_EQ(false, mtrx1 == mtrx2);
}

TEST(matrix_test, eq2) {
  S21Matrix mtrx1(3, 3);
  S21Matrix mtrx2(3, 3);
  ASSERT_EQ(true, mtrx1 == mtrx2);
}

TEST(matrix_test, eq3) {
  S21Matrix mtrx1(1, 1);
  S21Matrix mtrx2(1, 1);
  double arr1[] = {1.1};
  double arr2[] = {1.15};
  mtrx1.SetValues(arr1);
  mtrx2.SetValues(arr2);
  ASSERT_EQ(false, mtrx1 == mtrx2);
}

TEST(matrix_test, det1) {
  S21Matrix mtrx1(3, 3);
  double nums_array[] = {1, -3, 4, 2, 5, -3, 4, -2, 7};
  mtrx1.SetValues(nums_array);
  S21Matrix mtrx2 = mtrx1;
  ASSERT_EQ(11.0, mtrx2.Determinant());
}

TEST(matrix_test, det2) {
  S21Matrix mtrx1(3, 5);
  try {
    mtrx1.Determinant();
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Матрица должна быть квадратной"));
  }
}

TEST(matrix_test, compl1) {
  S21Matrix mtrx1(3, 5);
  try {
    mtrx1.CalcComplements();
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(), std::string("Матрица должна быть квадратной"));
  }
}

TEST(matrix_test, compl2) {
  S21Matrix mtrx1(3, 3);
  double nums_array[] = {1, -3, 4, 2, 5, -3, 4, -2, 7};
  mtrx1.SetValues(nums_array);
  S21Matrix mtrx2 = mtrx1.CalcComplements();
  double nums_array1[] = {29.0,  -26.0, -24.0, 13.0, -9.0,
                          -10.0, -11.0, 11.0,  11.0};
  int k = 0;
  for (int i = 0; i < mtrx1.GetRows(); i++)
    for (int j = 0; j < mtrx1.GetCols(); j++)
      ASSERT_EQ(mtrx2(i, j), nums_array1[k++]);
}

TEST(matrix_test, transpose) {
  S21Matrix mtrx1(3, 5);
  S21Matrix mtrx2 = mtrx1.Transpose();
  ASSERT_EQ(3, mtrx2.GetCols());
  ASSERT_EQ(5, mtrx2.GetRows());
}

TEST(matrix_test, resize) {
  S21Matrix mtrx1(3, 3);
  mtrx1.SetSize(5, 5);
  mtrx1.SetSize(1, 1);
  mtrx1.SetSize(8, 8);
  ASSERT_EQ(8, mtrx1.GetCols());
  ASSERT_EQ(8, mtrx1.GetRows());
}

TEST(matrix_test, inverse1) {
  S21Matrix mtrx1(3, 3);
  double nums_array[] = {1.0, -3.0, 4.0, 2.0, 5.0, -3.0, 4.0, -2.0, 7.0};
  mtrx1.SetValues(nums_array);
  S21Matrix mtrx2 = mtrx1.InverseMatrix();
  double nums_array1[] = {2.636363, 1.181818, -1.0,   -2.3636, -0.818181,
                          1.0,      -2.1818,  -0.909, 1.0};
  mtrx1.SetValues(nums_array1);
  int k = 0;
  for (int i = 0; i < mtrx2.GetRows(); i++) {
    for (int j = 0; j < mtrx2.GetCols(); j++) {
      EXPECT_LT(fabs(mtrx2(i, j) - nums_array1[k++]), 1e-4);
    }
  }
}

TEST(matrix_test, inverse2) {
  S21Matrix mtrx1(3, 3);
  mtrx1.FillMatrix();
  try {
    mtrx1.InverseMatrix();
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    ASSERT_EQ(err.what(),
              std::string("Определитель матрицы не может быть равен 0"));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
