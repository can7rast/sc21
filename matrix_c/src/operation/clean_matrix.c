#include "../s21_matrix.h"

void s21_free_matrix(matrix_t *res) {
  for (int i = 0; i < res->rows; i++) {
    free(res->matrix[i]);
    res->matrix[i] = NULL;
  }
  free(res->matrix);
  res->matrix = NULL;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix && A->rows && A->columns) {
      s21_free_matrix(A);
    }
    A->rows = 0;
    A->columns = 0;
    A = NULL;
  }
}
