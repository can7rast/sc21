#include "../s21_matrix.h"

int s21_exist_matrix(matrix_t *A) {
  int error = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  }
  return error;
}

int s21_check_matrix(matrix_t *A, matrix_t *B, matrix_t *res) {
  int error = 0;
  if (s21_exist_matrix(A) || s21_exist_matrix(B)) {
    error = 1;
  } else if (!s21_eq_size(A, B)) {
    error = 2;
  } else if (s21_create_matrix(A->rows, A->columns, res)) {
    error = 1;
  }

  return error;
}