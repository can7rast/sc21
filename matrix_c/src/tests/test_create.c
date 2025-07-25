#include "tests.h"

START_TEST(s21_create_matrix_1) {
  matrix_t m = {};
  ck_assert_int_eq(s21_create_matrix(3, 3, &m), 0);
  ck_assert_ptr_nonnull(m.matrix);
  ck_assert_int_eq(m.rows, 3);
  ck_assert_int_eq(m.columns, 3);
  for (int i = 0; i < m.rows; i++) {
    ck_assert_ptr_nonnull(m.matrix[i]);
  }
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  ck_assert_int_eq(s21_create_matrix(4, 4, NULL), 1);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t m = {};
  ck_assert_int_eq(s21_create_matrix(7, 0, &m), 1);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t m = {};
  ck_assert_int_eq(s21_create_matrix(0, 8, &m), 1);
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t m = {};
  int res = s21_create_matrix(1, 1, &m);
  ck_assert_int_eq(res, 0);
  ck_assert_ptr_nonnull(m.matrix);
  ck_assert_ptr_nonnull(m.matrix[0]);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_create_matrix_6) {
  matrix_t m = {};
  int res = s21_create_matrix(1, 2, &m);
  ck_assert_int_eq(res, 0);
  ck_assert_ptr_nonnull(m.matrix);
  ck_assert_ptr_nonnull(m.matrix[0]);
  s21_remove_matrix(&m);
}
END_TEST

Suite *s21_create_matrix_test(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("t21_create_matrix");
  tcase_add_test(tc, s21_create_matrix_1);
  tcase_add_test(tc, s21_create_matrix_2);
  tcase_add_test(tc, s21_create_matrix_3);
  tcase_add_test(tc, s21_create_matrix_4);
  tcase_add_test(tc, s21_create_matrix_5);
  tcase_add_test(tc, s21_create_matrix_6);
  suite_add_tcase(s, tc);

  return s;
}