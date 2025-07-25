#include "../s21_matrix.h"

int s21_eq_size(matrix_t *A, matrix_t *B) {
  int eq = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) {
    eq = FAILURE;
  }

  return eq;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int eq = SUCCESS;

  if (s21_eq_size(A, B)) {
    for (int i = 0; i < A->rows && eq; i++) {
      for (int j = 0; j < A->columns && eq; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
          eq = FAILURE;
        }
      }
    }
  } else {
    eq = FAILURE;
  }

  return eq;
}