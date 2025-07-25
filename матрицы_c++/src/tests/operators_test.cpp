#include "s21_matrix_oop_test.h"

// Тест оператора присваивания
TEST(OperatorTest, Assignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A = B;

  ASSERT_EQ(true, A.EqMatrix(B));
}

// Тест оператора через move
TEST(OperatorTest, MoveAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A = std::move(B);

  ASSERT_EQ(2, A.GetRows());
  ASSERT_EQ(2, A.GetCols());
  ASSERT_EQ(5, A(0, 0));
  ASSERT_EQ(6, A(0, 1));
  ASSERT_EQ(7, A(1, 0));
  ASSERT_EQ(8, A(1, 1));
}

// Тест оператора присваивания с 3 матрицами
TEST(OperatorTest, Assignment3Matrices) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  S21Matrix C(2, 2);
  C(0, 0) = 9;
  C(0, 1) = 10;
  C(1, 0) = 11;
  C(1, 1) = 12;

  A = B = C;

  ASSERT_EQ(true, A.EqMatrix(C));
  ASSERT_EQ(true, B.EqMatrix(C));
}

// Оператор сложения 2x2
TEST(OperatorTest, Addition) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A = A + B;

  S21Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Сложение 3x3
TEST(OperatorTest, Addition3x3) {
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
  B(0, 0) = 9;
  B(0, 1) = 8;
  B(0, 2) = 7;
  B(1, 0) = 6;
  B(1, 1) = 5;
  B(1, 2) = 4;
  B(2, 0) = 3;
  B(2, 1) = 2;
  B(2, 2) = 1;

  A = A + B;

  S21Matrix C(3, 3);
  C(0, 0) = 10;
  C(0, 1) = 10;
  C(0, 2) = 10;
  C(1, 0) = 10;
  C(1, 1) = 10;
  C(1, 2) = 10;
  C(2, 0) = 10;
  C(2, 1) = 10;
  C(2, 2) = 10;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Сложение матриц разной размерности
TEST(OperatorTest, AdditionDifferentDimensions) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B(3, 2);
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(1, 0) = 9;
  B(1, 1) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;

  ASSERT_THROW(A + B, std::invalid_argument);
}

// Тест оператора вычитания

// Тест 1 вычитание матрицы 2x2
TEST(OperatorTest, Subtraction2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A = B - A;

  S21Matrix C(2, 2);
  C(0, 0) = 4;
  C(0, 1) = 4;
  C(1, 0) = 4;
  C(1, 1) = 4;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 2 вычитание матрицы 3x3
TEST(OperatorTest, Subtraction3x3) {
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
  B(0, 0) = 9;
  B(0, 1) = 8;
  B(0, 2) = 7;
  B(1, 0) = 6;
  B(1, 1) = 5;
  B(1, 2) = 4;
  B(2, 0) = 3;
  B(2, 1) = 2;
  B(2, 2) = 1;

  A = A - B;

  S21Matrix C(3, 3);
  C(0, 0) = -8;
  C(0, 1) = -6;
  C(0, 2) = -4;
  C(1, 0) = -2;
  C(1, 1) = 0;
  C(1, 2) = 2;
  C(2, 0) = 4;
  C(2, 1) = 6;
  C(2, 2) = 8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 3 вычитание матриц разной размерности
TEST(OperatorTest, SubtractionDifferentDimensions) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B(3, 2);
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(1, 0) = 9;
  B(1, 1) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;

  ASSERT_THROW(A - B, std::invalid_argument);
}

// Тест оператора умножения

// Тест 1 умножение матрицы 2x2 на число
TEST(OperatorTest, MultiplicationByNumber2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double num = 2.0;
  A = A * num;

  S21Matrix C(2, 2);
  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 2 умножение матрицы 3x3 на число
TEST(OperatorTest, MultiplicationByNumber3x3) {
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

  double num = 3.5;

  A = A * num;

  S21Matrix C(3, 3);
  C(0, 0) = 3.5;
  C(0, 1) = 7.0;
  C(0, 2) = 10.5;
  C(1, 0) = 14.0;
  C(1, 1) = 17.5;
  C(1, 2) = 21.0;
  C(2, 0) = 24.5;
  C(2, 1) = 28.0;
  C(2, 2) = 31.5;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 3 умножение матрицы 2x3 на матрицу 3x2
TEST(OperatorTest, Multiplication2x3By3x2) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B(3, 2);
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(1, 0) = 9;
  B(1, 1) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;

  A = A * B;

  S21Matrix C(2, 2);
  C(0, 0) = 58;
  C(0, 1) = 64;
  C(1, 0) = 139;
  C(1, 1) = 154;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 4 умножение матрицы 3x2 на матрицу 2x3
TEST(OperatorTest, Multiplication3x2By2x3) {
  S21Matrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 5;
  A(2, 1) = 6;

  S21Matrix B(2, 3);
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(0, 2) = 9;
  B(1, 0) = 10;
  B(1, 1) = 11;
  B(1, 2) = 12;

  A = A * B;

  S21Matrix C(3, 3);
  C(0, 0) = 27;
  C(0, 1) = 30;
  C(0, 2) = 33;
  C(1, 0) = 61;
  C(1, 1) = 68;
  C(1, 2) = 75;
  C(2, 0) = 95;
  C(2, 1) = 106;
  C(2, 2) = 117;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест 5 умножение матриц с несовпадающими размерами столбцов
TEST(OperatorTest, MultiplicationDifferentDimensions) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B(4, 2);
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(1, 0) = 9;
  B(1, 1) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;
  B(3, 0) = 13;
  B(3, 1) = 14;

  ASSERT_THROW(A * B, std::invalid_argument);
}

// Тест оператора ==
TEST(OperatorTest, Equality) {
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

  ASSERT_EQ(true, A == B);
}

// тест с матрицей 1x1
TEST(OperatorTest, Equality1x1) {
  S21Matrix A(1, 1);
  A(0, 0) = 1;

  S21Matrix B(1, 1);
  B(0, 0) = 1;

  ASSERT_EQ(true, A == B);
}

// тест с матрицей 2x2 неравных
TEST(OperatorTest, Equality2x2NotEqual) {
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

  ASSERT_EQ(false, A == B);
}

// тест матриц с разной размерностью
TEST(OperatorTest, EqualityDifferentDimensions) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 4;
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 0) = 7;
  B(2, 1) = 8;
  B(2, 2) = 9;

  ASSERT_EQ(false, A == B);
}

// Тест оператора +=
TEST(OperatorTest, AdditionAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A += B;

  S21Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  ASSERT_EQ(true, A.EqMatrix(C));
}

// Тест с матрицами разной размерности
TEST(OperatorTest, AdditionAssignmentDifferentDimensions) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 3);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(0, 2) = 7;
  B(1, 0) = 8;
  B(1, 1) = 9;
  B(1, 2) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;
  B(2, 2) = 13;

  ASSERT_THROW(A += B, std::invalid_argument);
}

// Тест оператора -=
TEST(OperatorTest, SubtractionAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A -= B;

  S21Matrix C(2, 2);
  C(0, 0) = -4;
  C(0, 1) = -4;
  C(1, 0) = -4;
  C(1, 1) = -4;

  ASSERT_EQ(true, A == C);
}

// Тест с матрицами разной размерности
TEST(OperatorTest, SubtractionAssignmentDifferentDimensions) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 3);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(0, 2) = 7;
  B(1, 0) = 8;
  B(1, 1) = 9;
  B(1, 2) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;
  B(2, 2) = 13;

  ASSERT_THROW(A -= B, std::invalid_argument);
}

// Тест оператора *=
TEST(OperatorTest, MultiplicationAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double num = 2.0;
  A *= num;

  S21Matrix C(2, 2);
  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  ASSERT_EQ(true, A == C);
}

// Тест с матрицами разной размерности
TEST(OperatorTest, MultiplicationAssignmentDifferentDimensions) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(3, 3);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(0, 2) = 7;
  B(1, 0) = 8;
  B(1, 1) = 9;
  B(1, 2) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;
  B(2, 2) = 13;

  ASSERT_THROW(A *= B, std::invalid_argument);
}

// Тест умножение матрицы на другую матрицу
TEST(OperatorTest, MultiplicationMatrixByMatrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A = A * B;

  S21Matrix C(2, 2);
  C(0, 0) = 19;
  C(0, 1) = 22;
  C(1, 0) = 43;
  C(1, 1) = 50;

  ASSERT_EQ(true, A == C);
}

// Тест оператора ()
TEST(OperatorTest, Brackets) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  ASSERT_EQ(1, A(0, 0));
  ASSERT_EQ(2, A(0, 1));
  ASSERT_EQ(3, A(1, 0));
  ASSERT_EQ(4, A(1, 1));

  A(0, 0) = 10;
  ASSERT_EQ(10, A(0, 0));
}
