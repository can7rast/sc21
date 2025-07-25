#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (s21_exist_matrix(A)) {
    error = 1;
  }

  if (error == 0 && !s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) {
          error = 2;
        }
      }
    }
  }
  if (error == 2) {
    s21_remove_matrix(result);
  }

  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (s21_exist_matrix(A) || s21_exist_matrix(B) ||
      s21_create_matrix(A->rows, B->columns, result)) {
    error = 1;
  } else if (A->columns != B->rows) {
    error = 2;
  }

  if (error == 0) {
    error = s21_m_matrix(A, B, result);
  }

  if (error == 2) {
    s21_remove_matrix(result);
  }

  return error;
}

int s21_m_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        double temp = A->matrix[i][k] * B->matrix[k][j];
        result->matrix[i][j] += temp;
      }
    }
  }

  for (int i = 0; i < result->rows && !error; i++) {
    for (int j = 0; j < result->columns && !error; j++) {
      if (!isfinite(result->matrix[i][j])) error = 2;
    }
  }

  return error;
}