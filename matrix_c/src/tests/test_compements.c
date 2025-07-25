#include "tests.h"

// Тест 1 : Успешное вычисление

START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(3, 3);

  s21_fill(&A, 1);
  A.matrix[1][0] = 0;

  matrix_t res = {};

  int error = s21_calc_complements(&A, &res);

  matrix_t eq = s21_create_test_matrix(3, 3);

  eq.matrix[0][0] = -3;
  eq.matrix[0][1] = 42;
  eq.matrix[0][2] = -35;
  eq.matrix[1][0] = 6;
  eq.matrix[1][1] = -12;
  eq.matrix[1][2] = 6;
  eq.matrix[2][0] = -3;
  eq.matrix[2][1] = -6;
  eq.matrix[2][2] = 5;

  int equal = s21_eq_matrix(&res, &eq);

  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(error, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 2 : успешное выполнение
START_TEST(test2) {
  matrix_t A = s21_create_test_matrix(3, 3);

  s21_fill(&A, 1);

  matrix_t res = {};

  int error = s21_calc_complements(&A, &res);

  matrix_t eq = s21_create_test_matrix(3, 3);

  eq.matrix[0][0] = -3;
  eq.matrix[0][1] = 6;
  eq.matrix[0][2] = -3;
  eq.matrix[1][0] = 6;
  eq.matrix[1][1] = -12;
  eq.matrix[1][2] = 6;
  eq.matrix[2][0] = -3;
  eq.matrix[2][1] = 6;
  eq.matrix[2][2] = -3;

  int equal = s21_eq_matrix(&res, &eq);

  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(error, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 3: некорректные данные
START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);
  matrix_t res = {};

  ck_assert_int_eq(1, s21_calc_complements(NULL, &res));
  ck_assert_int_eq(1, s21_calc_complements(&A, NULL));
  ck_assert_int_eq(1, s21_calc_complements(NULL, NULL));

  s21_remove_matrix(&A);
}
END_TEST

// Тест 4 : Прямоугольная матрица
START_TEST(test4) {
  matrix_t A = s21_create_test_matrix(2, 1);
  s21_fill(&A, 1);

  matrix_t res = {};

  int error = s21_calc_complements(&A, &res);
  ck_assert_int_eq(error, 1);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_compements_test(void) {
  Suite *s = suite_create("s21_compements");
  TCase *tc = tcase_create("t21_compements");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);

  suite_add_tcase(s, tc);

  return s;
}