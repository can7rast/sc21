#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (s21_exist_matrix(A) || result == NULL || A->columns != A->rows) {
    error = 1;
  }
  if (!error) {
    double det = 0;
    error += s21_determinant(A, &det);
    if (!error) {
      error = s21_create_matrix(A->rows, A->columns, result);
    }

    if (!error && det != 0) {
      matrix_t B;
      error = s21_calc_complements(A, &B);
      if (!error) {
        matrix_t C;
        error = s21_transpose(&B, &C);
        error += s21_mult_number(&C, 1 / det, result);
        s21_remove_matrix(&C);
      }
      s21_remove_matrix(&B);
    }
    if (det == 0) {
      error = 2;
    }
  }

  return error;
}