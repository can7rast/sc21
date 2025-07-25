#include "tests.h"

// Тест 1 : Успешное нахождение
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);
  A.matrix[1][0] = 0;
  A.matrix[2][0] = 0;

  matrix_t res = {};
  int error = s21_inverse_matrix(&A, &res);

  matrix_t eq = s21_create_test_matrix(3, 3);
  eq.matrix[0][0] = 1;
  eq.matrix[0][1] = -2;
  eq.matrix[0][2] = 1;
  eq.matrix[1][0] = 0;
  eq.matrix[1][1] = -3;
  eq.matrix[1][2] = 2;
  eq.matrix[2][0] = 0;
  eq.matrix[2][1] = 8.0 / 3.0;
  eq.matrix[2][2] = -5.0 / 3.0;

  int equal = s21_eq_matrix(&res, &eq);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(equal, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 2 : матрица размера 2x2
START_TEST(test2) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);
  matrix_t res = {};
  matrix_t eq = s21_create_test_matrix(2, 2);

  int error = s21_inverse_matrix(&A, &res);

  eq.matrix[0][0] = -2;
  eq.matrix[0][1] = 1;
  eq.matrix[1][0] = 1.5;
  eq.matrix[1][1] = -0.5;

  int equal = s21_eq_matrix(&eq, &res);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(equal, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 3 : det = 0
START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(2, 2);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  matrix_t res = {};

  int error = s21_inverse_matrix(&A, &res);

  ck_assert_int_eq(error, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

// Тест 4 : некоректные данные
START_TEST(test4) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);

  matrix_t res = {};

  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &res), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_inverse_test(void) {
  Suite *s = suite_create("s21_inverse_matr");
  TCase *tc = tcase_create("t21_inverse_matr");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);

  suite_add_tcase(s, tc);

  return s;
}