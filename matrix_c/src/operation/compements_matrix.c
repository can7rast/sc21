#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (s21_exist_matrix(A) || s21_create_matrix(A->rows, A->columns, result) ||
      A->columns != A->rows) {
    error = 1;
  }
  if (!error) {
    for (int i = 0; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        double temp = 0;
        matrix_t C;
        error = s21_create_matrix(A->rows - 1, A->columns - 1, &C);
        if (!error) {
          error = s21_fill_minor(i, j, A, &C);
        }
        if (!error) {
          error = s21_determinant(&C, &temp);
        }
        if (!error) {
          result->matrix[i][j] = temp * pow(-1, i + j);
        }
        s21_remove_matrix(&C);
      }
    }
  }

  return error;
}
