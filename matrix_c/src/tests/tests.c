#include "tests.h"

int main(void) {
  int number_failed = 0;
  SRunner *sr;
  sr = srunner_create(s21_create_matrix_test());
  srunner_add_suite(sr, s21_remove_matrix_test());
  srunner_add_suite(sr, s21_sum_matrix_test());
  srunner_add_suite(sr, s21_eq_matrix_test());
  srunner_add_suite(sr, s21_sub_matrix_test());
  srunner_add_suite(sr, s21_mult_number_test());

  srunner_add_suite(sr, s21_mult_matr_test());
  srunner_add_suite(sr, s21_transpose_test());
  srunner_add_suite(sr, s21_compements_test());
  srunner_add_suite(sr, s21_determinant_test());
  srunner_add_suite(sr, s21_inverse_test());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
