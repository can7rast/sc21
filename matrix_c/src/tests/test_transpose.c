#include "tests.h"

// Тест 1: Успешное траспонирование
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);

  matrix_t res = {};

  int error = s21_transpose(&A, &res);

  matrix_t eq = s21_create_test_matrix(2, 2);

  eq.matrix[0][0] = 1;
  eq.matrix[0][1] = 3;
  eq.matrix[1][0] = 2;
  eq.matrix[1][1] = 4;

  int equal = s21_eq_matrix(&res, &eq);

  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(error, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&eq);
  s21_remove_matrix(&res);
}
END_TEST

// Тест 2: Успешное траспонирование 3x3

START_TEST(test2) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);

  matrix_t res = {};

  int error = s21_transpose(&A, &res);

  matrix_t eq = s21_create_test_matrix(3, 3);

  eq.matrix[0][0] = 1;
  eq.matrix[0][1] = 4;
  eq.matrix[0][2] = 7;
  eq.matrix[1][0] = 2;
  eq.matrix[1][1] = 5;
  eq.matrix[1][2] = 8;
  eq.matrix[2][0] = 3;
  eq.matrix[2][1] = 6;
  eq.matrix[2][2] = 9;

  int equal = s21_eq_matrix(&res, &eq);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(equal, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&eq);
  s21_remove_matrix(&res);
}
END_TEST

// Тест 3:некорректные данные
START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);

  matrix_t res = {};

  int error = s21_transpose(&A, NULL);

  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(1, s21_transpose(NULL, &res));

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_transpose_test(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("t21_transpose");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);

  suite_add_tcase(s, tc);

  return s;
}