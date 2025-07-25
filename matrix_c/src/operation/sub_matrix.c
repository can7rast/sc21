#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = s21_check_matrix(A, B, result);

  if (!error) {
    for (int i = 0; i < A->rows && !error; i++)
      for (int j = 0; j < A->columns && !error; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) {
          error = 1;
        }
      }
  }

  return error;
}
