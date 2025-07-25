#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>

#include "../s21_matrix.h"

Suite *s21_create_matrix_test(void);
Suite *s21_remove_matrix_test(void);
Suite *s21_sum_matrix_test(void);
Suite *s21_eq_matrix_test(void);
Suite *s21_sub_matrix_test(void);
Suite *s21_mult_number_test(void);
Suite *s21_mult_matr_test(void);
Suite *s21_transpose_test(void);
Suite *s21_compements_test(void);
Suite *s21_determinant_test(void);
Suite *s21_inverse_test(void);

#endif