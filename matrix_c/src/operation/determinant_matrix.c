#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;

  if (s21_exist_matrix(A) || A->columns != A->rows || result == NULL) {
    error = 1;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      s21_based_minor(A, result);
    } else {
      int k = 0, n = A->columns;
      double *str = A->matrix[0];
      *result = 0;
      while (k < n && !error) {
        matrix_t B;
        error = s21_create_matrix(A->rows - 1, A->columns - 1, &B);
        if (!error) error = s21_fill_minor(0, k, A, &B);
        if (!error) {
          double temp = 0;
          error = s21_determinant(&B, &temp);
          *result += str[k] * pow(-1, k) * temp;
        }
        s21_remove_matrix(&B);
        k++;
      }
    }
  }

  return error;
}

int s21_fill_minor(int k, int z, matrix_t *A, matrix_t *B) {
  int error = 0;
  if (s21_exist_matrix(A) || s21_exist_matrix(B)) {
    error = 1;
  } else {
    int y = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i != k) {
        int x = 0;
        for (int j = 0; j < A->columns; j++) {
          if (j != z) {
            B->matrix[y][x] = A->matrix[i][j];
            x++;
          }
        }
        y++;
      }
    }
  }

  return error;
}