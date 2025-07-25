#include "tests.h"

START_TEST(s21_remove_matrix_1) {
  matrix_t M = {};
  s21_create_matrix(3, 3, &M);
  s21_remove_matrix(&M);
  ck_assert_ptr_null(M.matrix);
}
END_TEST

Suite *s21_remove_matrix_test(void) {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("t21_remove_matrix");
  tcase_add_test(tc, s21_remove_matrix_1);
  suite_add_tcase(s, tc);

  return s;
}