#include "tests.h"

// Успешное умножение
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 2);  // A = [[2, 3], [4, 5]]

  double m = 2;
  matrix_t res = {};

  int error = 0;
  error = s21_mult_number(&A, m, &res);

  matrix_t e = s21_create_test_matrix(2, 2);
  e.matrix[0][0] = 4;
  e.matrix[0][1] = 6;
  e.matrix[1][0] = 8;
  e.matrix[1][1] = 10;

  int equal = s21_eq_matrix(&res, &e);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(equal, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&e);
  s21_remove_matrix(&res);
}
END_TEST

// Тест 2: Некорректные входные данные (NULL)
START_TEST(test2) {
  matrix_t result = {};

  int error = s21_mult_number(NULL, 1, &result);

  ck_assert_int_eq(error, 1);

  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: нет нормального double

START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);

  matrix_t result = {};

  int error = s21_mult_number(&A, NAN, &result);

  ck_assert_int_eq(error, 2);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 4: Получаем бесконечность
START_TEST(test4) {
  matrix_t A = s21_create_test_matrix(1, 1);
  matrix_t result = {};
  A.matrix[0][0] = MAXDOUBLE;

  int error = s21_mult_number(&A, MAXDOUBLE, &result);

  ck_assert_int_eq(error, 2);
}
END_TEST

Suite *s21_mult_number_test(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("t21_mult_number");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);

  suite_add_tcase(s, tc);

  return s;
}