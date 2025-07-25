#include "tests.h"

// Тест 1 : успешное вычисление
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);

  double res = 1;

  int error = s21_determinant(&A, &res);

  ck_assert_int_eq(0, error);
  ck_assert_double_eq(res, 0.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 2 : успешное вычисление
START_TEST(test2) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);
  A.matrix[1][0] = 0;

  double res = 0;

  int error = s21_determinant(&A, &res);

  ck_assert_int_eq(0, error);
  ck_assert_double_eq(res, -24.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 3 : не квадратная матрица
START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(2, 1);
  s21_fill(&A, 1);

  double res = 0;

  int error = s21_determinant(&A, &res);
  ck_assert_int_eq(error, 1);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 4 : матрица 1x1
START_TEST(test4) {
  matrix_t A = s21_create_test_matrix(1, 1);
  s21_fill(&A, 1);

  double res = 0;

  int error = s21_determinant(&A, &res);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 5 : Некорректные данные

START_TEST(test5) {
  matrix_t A = s21_create_test_matrix(1, 1);
  s21_fill(&A, 1);
  double res = 0;
  ck_assert_int_eq(1, s21_determinant(NULL, &res));
  ck_assert_int_eq(1, s21_determinant(&A, NULL));
  ck_assert_int_eq(1, s21_determinant(NULL, NULL));

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_test(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc = tcase_create("t21_determinant");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);

  suite_add_tcase(s, tc);

  return s;
}