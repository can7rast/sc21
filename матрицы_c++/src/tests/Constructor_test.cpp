#include "s21_matrix_oop_test.h"

TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix A;
  ASSERT_EQ(1, A.GetRows());
  ASSERT_EQ(1, A.GetCols());
  ASSERT_EQ(0, A(0, 0));
}

TEST(ConstructorTest, ParameterizedConstructor) {
  S21Matrix A(3, 4);
  ASSERT_EQ(3, A.GetRows());
  ASSERT_EQ(4, A.GetCols());
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      ASSERT_EQ(0, A(i, j));
    }
  }
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(A);
  ASSERT_EQ(2, B.GetRows());
  ASSERT_EQ(2, B.GetCols());
  ASSERT_EQ(1.0, B(0, 0));
  ASSERT_EQ(2.0, B(0, 1));
  ASSERT_EQ(3.0, B(1, 0));
  ASSERT_EQ(4.0, B(1, 1));
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;

  S21Matrix B(std::move(A));
  ASSERT_EQ(2, B.GetRows());
  ASSERT_EQ(3, B.GetCols());
  ASSERT_EQ(1.0, B(0, 0));
  ASSERT_EQ(2.0, B(0, 1));
  ASSERT_EQ(3.0, B(0, 2));
  ASSERT_EQ(4.0, B(1, 0));
  ASSERT_EQ(5.0, B(1, 1));
  ASSERT_EQ(6.0, B(1, 2));

  ASSERT_EQ(0, A.GetRows());
  ASSERT_EQ(0, A.GetCols());
}

TEST(ConstructorTest, InvalidDimensions) {
  ASSERT_THROW(S21Matrix A(-1, 5), std::invalid_argument);
  ASSERT_THROW(S21Matrix A(5, -1), std::invalid_argument);
  ASSERT_THROW(S21Matrix A(0, 5), std::invalid_argument);
  ASSERT_THROW(S21Matrix A(5, 0), std::invalid_argument);
}

TEST(ConstructorTest, InvalidIndexAccess) {
  S21Matrix A(2, 2);
  ASSERT_THROW(A(-1, 0), std::out_of_range);
  ASSERT_THROW(A(0, -1), std::out_of_range);
  ASSERT_THROW(A(2, 0), std::out_of_range);
  ASSERT_THROW(A(0, 2), std::out_of_range);
}

TEST(ConstructorTest, CopyFromInvalidMatrix) {
  S21Matrix A(1, 1);
  A(0, 0) = 1.0;

  // Attempt to create matrix with invalid dimensions
  ASSERT_THROW({ A.SetRows(-1); }, std::invalid_argument);

  ASSERT_THROW({ A.SetCols(-1); }, std::invalid_argument);
}
