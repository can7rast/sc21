#include "tests.h"

// Тест 1: успешное умножение матриц 1x1
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(1, 1);
  matrix_t B = s21_create_test_matrix(1, 1);

  A.matrix[0][0] = 5;
  B.matrix[0][0] = 10;

  matrix_t result = {};

  int error = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_double_eq(result.matrix[0][0], 50.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: успешное умножение матриц 3x3
START_TEST(test2) {
  matrix_t A = s21_create_test_matrix(3, 3);
  s21_fill(&A, 1);

  matrix_t B = s21_create_test_matrix(3, 3);
  s21_fill(&B, 10);

  matrix_t result = {};

  int error = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(error, 0);

  matrix_t eq = s21_create_test_matrix(3, 3);
  eq.matrix[0][0] = 84;
  eq.matrix[0][1] = 90;
  eq.matrix[0][2] = 96;

  eq.matrix[1][0] = 201;
  eq.matrix[1][1] = 216;
  eq.matrix[1][2] = 231;

  eq.matrix[2][0] = 318;
  eq.matrix[2][0] = 342;
  eq.matrix[2][0] = 366;

  int equal = s21_eq_matrix(&result, &eq);

  ck_assert_int_eq(equal, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 3: успешное умножение матриц разных размеров
START_TEST(test3) {
  matrix_t A = s21_create_test_matrix(2, 3);
  s21_fill(&A, 1);

  matrix_t B = s21_create_test_matrix(3, 2);
  s21_fill(&B, 5);

  matrix_t result = {};

  int error = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_ptr_nonnull(result.matrix);

  matrix_t eq = s21_create_test_matrix(2, 2);
  eq.matrix[0][0] = 46;
  eq.matrix[0][1] = 52;
  eq.matrix[1][0] = 109;
  eq.matrix[1][1] = 124;

  int equal = s21_eq_matrix(&result, &eq);
  ck_assert_int_eq(equal, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq);
}
END_TEST

// Тест 4: разные размеры
START_TEST(test4) {
  matrix_t A = s21_create_test_matrix(2, 3);
  matrix_t B = s21_create_test_matrix(4, 5);
  matrix_t result = {};

  int error = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 5:некорректные данные
START_TEST(test5) {
  matrix_t A = s21_create_test_matrix(2, 2);
  s21_fill(&A, 1);
  matrix_t res = {};
  ck_assert_int_eq(1, s21_mult_matrix(NULL, &A, &res));
  ck_assert_int_eq(1, s21_mult_matrix(&A, NULL, &res));
  ck_assert_int_eq(1, s21_mult_matrix(NULL, NULL, &res));
  ck_assert_int_eq(1, s21_mult_matrix(&A, &A, NULL));

  s21_remove_matrix(&A);
}
END_TEST

// Тест 6: переполнение double
START_TEST(test6) {
  matrix_t A = s21_create_test_matrix(1, 1);
  matrix_t B = s21_create_test_matrix(1, 1);
  A.matrix[0][0] = MAXDOUBLE;
  B.matrix[0][0] = MAXDOUBLE;

  matrix_t result = {};

  int error = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(error, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_mult_matr_test(void) {
  Suite *s = suite_create("s21_mult_matr");
  TCase *tc = tcase_create("t21_mult_matr");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);

  suite_add_tcase(s, tc);

  return s;
}