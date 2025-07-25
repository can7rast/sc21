#include "s21_matrix_oop_test.h"

// тесты на геттеры
TEST(AccessorTest, GetRows) {
  S21Matrix A(3, 4);
  ASSERT_EQ(3, A.GetRows());
}

TEST(AccessorTest, GetCols) {
  S21Matrix A(3, 4);
  ASSERT_EQ(4, A.GetCols());
}

// тесты на сеттеры
TEST(MutatorTest, SetRows) {
  S21Matrix A(3, 4);
  ASSERT_EQ(3, A.GetRows());
  A.SetRows(2);
  ASSERT_EQ(2, A.GetRows());
}

TEST(MutatorTest, SetRowsNegativeANDZero) {
  S21Matrix A(3, 4);
  ASSERT_THROW(A.SetRows(-1), std::invalid_argument);
  ASSERT_THROW(A.SetRows(0), std::invalid_argument);
}

TEST(MutatorTest, SetRowsSame) {
  S21Matrix A(3, 4);
  A.SetRows(3);
  ASSERT_EQ(3, A.GetRows());
}

TEST(MutatorTest, SetRowsNew) {
  S21Matrix A(3, 4);
  A.SetRows(5);
  ASSERT_EQ(5, A.GetRows());
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      ASSERT_EQ(A(i, j), 0.0);
    }
  }
}

TEST(MutatorTest, SetCols) {
  S21Matrix A(3, 4);
  ASSERT_EQ(4, A.GetCols());
  A.SetCols(2);
  ASSERT_EQ(2, A.GetCols());
}

TEST(MutatorTest, SetColsNegativeANDZero) {
  S21Matrix A(3, 4);
  ASSERT_THROW(A.SetCols(-1), std::invalid_argument);
  ASSERT_THROW(A.SetCols(0), std::invalid_argument);
}

TEST(MutatorTest, SetColsSame) {
  S21Matrix A(3, 4);
  A.SetCols(4);
  ASSERT_EQ(4, A.GetCols());
}

TEST(MutatorTest, SetColsNew) {
  S21Matrix A(3, 4);
  A.SetCols(5);
  ASSERT_EQ(5, A.GetCols());
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_EQ(A(i, j), 0.0);
    }
  }
}

// Тесты методов

// Тесты на равные матрицы
TEST(EqualTest, EQ_Matrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  ASSERT_EQ(true, A.EqMatrix(B));
}

// Тест матрицы не равны
TEST(EqualTest, NEQ_Matrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 5;

  ASSERT_EQ(false, A.EqMatrix(B));
}

// Тест матрицы имеют разные размеры
TEST(EqualTest, NEQ_Matrix_Different_Size) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  ASSERT_EQ(false, A.EqMatrix(B));
}

// Тест матрицы имеют разные размеры№2
TEST(EqualTest, NEQ_Matrix_Different_Size_2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 4;
  B(1, 1) = 5;
  B(1, 2) = 6;

  ASSERT_EQ(false, A.EqMatrix(B));
}

// Тест суммы матриц
TEST(SumTest, Sum_Matrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  A.SumMatrix(B);

  S21Matrix C(2, 2);
  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест суммы матриц с разными размерами
TEST(SumTest, Sum_Matrix_Different_Size) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 4;
  B(1, 1) = 5;
  B(1, 2) = 6;

  ASSERT_THROW(A.SumMatrix(B), std::invalid_argument);
}

// Тест суммы матриц с разными размерами№2
TEST(SumTest, Sum_Matrix_Different_Size_2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  B(2, 0) = 5;
  B(2, 1) = 6;

  ASSERT_THROW(A.SumMatrix(B), std::invalid_argument);
}

// Тест разности матриц
TEST(SubTest, Sub_Matrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  A.SubMatrix(B);

  S21Matrix C(2, 2);
  C(0, 0) = 0;
  C(0, 1) = 0;
  C(1, 0) = 0;
  C(1, 1) = 0;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест разности матриц с разными размерами
TEST(SubTest, Sub_Matrix_Different_Size) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 4;
  B(1, 1) = 5;
  B(1, 2) = 6;

  ASSERT_THROW(A.SubMatrix(B), std::invalid_argument);
}

// Тест разности матриц
TEST(SubTest, Sub_Matrix__2) {
  S21Matrix A(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }

  S21Matrix B(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = i + j;
    }
  }

  A.SubMatrix(B);

  S21Matrix C(4, 4);

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест умножения матрицы на число
TEST(MulNumberTest, Mul_Matrix_Number) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double number = 2;

  A.MulNumber(number);

  S21Matrix C(2, 2);
  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест умножения матрицы на число с отрицательным числом
TEST(MulNumberTest, Mul_Matrix_Number_Negative) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double number = -2;

  A.MulNumber(number);

  S21Matrix C(2, 2);
  C(0, 0) = -2;
  C(0, 1) = -4;
  C(1, 0) = -6;
  C(1, 1) = -8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест умножения матрицы на число с дробным числом
TEST(MulNumberTest, Mul_Matrix_Number_Fraction) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double number = 0.5;

  A.MulNumber(number);

  S21Matrix C(2, 2);
  C(0, 0) = 0.5;
  C(0, 1) = 1;
  C(1, 0) = 1.5;
  C(1, 1) = 2;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест умножения матрицы на число с дробным числом
TEST(MulNumberTest, Mul_Matrix_Number_Fraction_2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double number = 0.2;

  A.MulNumber(number);

  S21Matrix C(2, 2);
  C(0, 0) = 0.2;
  C(0, 1) = 0.4;
  C(1, 0) = 0.6;
  C(1, 1) = 0.8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест умножения матрицы на матрицу

// Тест 1 умножение матриц 1x1
TEST(MulMatrixTest, Mul_Matrix1) {
  S21Matrix A(1, 1);
  A(0, 0) = 5;

  S21Matrix B(1, 1);
  B(0, 0) = 10;

  A.MulMatrix(B);

  S21Matrix C(1, 1);
  C(0, 0) = 50;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 2 умножение матриц 3x3
TEST(MulMatrixTest, Mul_Matrix2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  S21Matrix B(3, 3);
  B(0, 0) = 10;
  B(0, 1) = 11;
  B(0, 2) = 12;
  B(1, 0) = 13;
  B(1, 1) = 14;
  B(1, 2) = 15;
  B(2, 0) = 16;
  B(2, 1) = 17;
  B(2, 2) = 18;

  A.MulMatrix(B);

  S21Matrix C(3, 3);
  C(0, 0) = 1 * 10 + 2 * 13 + 3 * 16;
  C(0, 1) = 1 * 11 + 2 * 14 + 3 * 17;
  C(0, 2) = 1 * 12 + 2 * 15 + 3 * 18;
  C(1, 0) = 4 * 10 + 5 * 13 + 6 * 16;
  C(1, 1) = 4 * 11 + 5 * 14 + 6 * 17;
  C(1, 2) = 4 * 12 + 5 * 15 + 6 * 18;
  C(2, 0) = 7 * 10 + 8 * 13 + 9 * 16;
  C(2, 1) = 7 * 11 + 8 * 14 + 9 * 17;
  C(2, 2) = 7 * 12 + 8 * 15 + 9 * 18;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 3 успешное умножение матриц разных размеров
TEST(MulMatrixTest, Mul_Matrix3) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B(3, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;

  A.MulMatrix(B);

  S21Matrix C(2, 2);
  C(0, 0) = 1 * 5 + 2 * 7 + 3 * 9;
  C(0, 1) = 1 * 6 + 2 * 8 + 3 * 10;
  C(1, 0) = 4 * 5 + 5 * 7 + 6 * 9;
  C(1, 1) = 4 * 6 + 5 * 8 + 6 * 10;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 4 умножение матрицы на матрицу с несовпадающими размерами
TEST(MulMatrixTest, Mul_Matrix4) {
  S21Matrix A(2, 3);
  S21Matrix B(4, 5);

  ASSERT_THROW(A.MulMatrix(B), std::invalid_argument);
}

// Тест 5 умножение матрицы на матрицу с несовпадающими размерами№2

TEST(MulMatrixTest, Mul_Matrix5) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 3);

  ASSERT_THROW(A.MulMatrix(B), std::invalid_argument);
}

// Тест транспонирования матрицы

// Тест 1 успешное транспонирование матрицы 2x2
TEST(TransposeTest, Transpose_Matrix1) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B = A.Transpose();

  S21Matrix C(2, 2);
  C(0, 0) = 1;
  C(0, 1) = 3;
  C(1, 0) = 2;
  C(1, 1) = 4;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 2 успешное транспонирование матрицы 3x3
TEST(TransposeTest, Transpose_Matrix2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  S21Matrix B = A.Transpose();

  S21Matrix C(3, 3);
  C(0, 0) = 1;
  C(0, 1) = 4;
  C(0, 2) = 7;
  C(1, 0) = 2;
  C(1, 1) = 5;
  C(1, 2) = 8;
  C(2, 0) = 3;
  C(2, 1) = 6;
  C(2, 2) = 9;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 3 транспонирование матрицы 1x4
TEST(TransposeTest, Transpose_Matrix3) {
  S21Matrix A(1, 4);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;

  S21Matrix B = A.Transpose();

  S21Matrix C(4, 1);
  C(0, 0) = 1;
  C(1, 0) = 2;
  C(2, 0) = 3;
  C(3, 0) = 4;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест вычисление алгебраического дополнения

// Тест 1 вычисление алгебраического дополнения матрицы 3x3
TEST(CalcComplementsTest, Calc_Complements1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  A(1, 0) = 0;

  S21Matrix B = A.CalcComplements();

  S21Matrix C(3, 3);

  C(0, 0) = -3;
  C(0, 1) = 42;
  C(0, 2) = -35;
  C(1, 0) = 6;
  C(1, 1) = -12;
  C(1, 2) = 6;
  C(2, 0) = -3;
  C(2, 1) = -6;
  C(2, 2) = 5;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 2 вычисление алгебраического дополнения матрицы 3x3
TEST(CalcComplementsTest, Calc_Complements2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  S21Matrix B = A.CalcComplements();

  S21Matrix C(3, 3);

  C(0, 0) = -3;
  C(0, 1) = 6;
  C(0, 2) = -3;
  C(1, 0) = 6;
  C(1, 1) = -12;
  C(1, 2) = 6;
  C(2, 0) = -3;
  C(2, 1) = 6;
  C(2, 2) = -3;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 3 Матрица прямоугольная
TEST(CalcComplementsTest, Calc_Complements3) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  ASSERT_THROW(A.CalcComplements(), std::invalid_argument);
}

// Тест Determinant

// Тест 1 определитель матрицы 3x3
TEST(DeterminantTest, Determinant_Matrix3) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  double det = A.Determinant();
  ASSERT_EQ(det, 0);
}

// Тест 2 определитель матрицы 3x3
TEST(DeterminantTest, Determinant_Matrix3_2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  double det = A.Determinant();
  ASSERT_EQ(det, -24.0);
}

// Тест 3 не квадратная матрица
TEST(DeterminantTest, Determinant_Not_Square) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  ASSERT_THROW(A.Determinant(), std::invalid_argument);
}

// Тест 4 матрица 1x1
TEST(DeterminantTest, Determinant_Matrix1) {
  S21Matrix A(1, 1);
  A(0, 0) = 1;

  double det = A.Determinant();
  ASSERT_EQ(det, 1);
}

// Тест обратная матрица

// Тест 1 обратная матрица 3x3
TEST(InverseMatrixTest, Inverse_Matrix1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 0;
  A(2, 1) = 8;
  A(2, 2) = 9;

  S21Matrix B = A.InverseMatrix();

  S21Matrix C(3, 3);
  C(0, 0) = 1;
  C(0, 1) = -2;
  C(0, 2) = 1;
  C(1, 0) = 0;
  C(1, 1) = -3;
  C(1, 2) = 2;
  C(2, 0) = 0;
  C(2, 1) = 8.0 / 3.0;
  C(2, 2) = -5.0 / 3.0;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 2 матрица 2x2
TEST(InverseMatrixTest, Inverse_Matrix2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B = A.InverseMatrix();

  S21Matrix C(2, 2);
  C(0, 0) = -2;
  C(0, 1) = 1;
  C(1, 0) = 1.5;
  C(1, 1) = -0.5;

  ASSERT_EQ(true, B.EqMatrix(C));
}

// Тест 3 det = 0
TEST(InverseMatrixTest, Inverse_Matrix3) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 2;
  A(1, 1) = 4;

  ASSERT_THROW(A.InverseMatrix(), std::invalid_argument);
}

// Тест 4 не квадратная матрица
TEST(InverseMatrixTest, Inverse_Matrix4) {
  S21Matrix A(2, 3);

  ASSERT_THROW(A.InverseMatrix(), std::invalid_argument);
}