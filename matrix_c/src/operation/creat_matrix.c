#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (result == NULL || (rows <= 0 || columns <= 0)) {
    error = 1;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      error = s21_fill_matrix(result);
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_fill_matrix(matrix_t *res) {
  int error = 0;
  for (int i = 0; i < res->rows && !error; i++) {
    res->matrix[i] = calloc(res->columns, sizeof(double));
    if (res->matrix[i] == NULL) {
      error = 1;
    }
  }
  if (error) {
    s21_free_matrix(res);
  }

  return error;
}