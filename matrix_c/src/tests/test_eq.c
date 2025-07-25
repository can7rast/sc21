#include "tests.h"

// Тест 1 успешное сравнение
START_TEST(test1) {
  matrix_t A = {};
  s21_create_matrix(2, 2, &A);
  s21_fill(&A, 1);

  matrix_t B = {};
  s21_create_matrix(2, 2, &B);
  s21_fill(&B, 1);

  int error = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(error, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест2 разные размеры

START_TEST(test2) {
  matrix_t A = {};
  s21_create_matrix(2, 2, &A);
  s21_fill(&A, 1);

  matrix_t B = {};
  s21_create_matrix(2, 3, &B);
  s21_fill(&B, 2);

  int error = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(error, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест3 сравнение 7ого знака

START_TEST(test3) {
  matrix_t A = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  matrix_t B = {};
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1.0000001;
  B.matrix[0][1] = 2.0000001;
  B.matrix[1][0] = 3.0000001;
  B.matrix[1][1] = 4.0000001;

  int error = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(error, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест4 удачное сравнение 7ого знака

START_TEST(test4) {
  matrix_t A = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  matrix_t B = {};
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1.00000009;
  B.matrix[0][1] = 2.00000009;
  B.matrix[1][0] = 3.00000009;
  B.matrix[1][1] = 4.00000009;

  int error = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(error, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_eq_matrix_test(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("t21_eq_matrix");
  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  suite_add_tcase(s, tc);

  return s;
}