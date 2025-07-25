#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (s21_exist_matrix(A) || result == NULL ||
      s21_create_matrix(A->columns, A->rows, result)) {
    error = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}

// int main()
// {
//   matrix_t A = s21_create_test_matrix(2,2);
//     s21_fill(&A,1);

//     matrix_t res = {};

//     int error = s21_transpose(&A, &res);
//     s21_print(&res);
//     matrix_t eq = s21_create_test_matrix(2,2);

//     eq.matrix[0][0] = 1;
//     eq.matrix[0][1] = 3;
//     eq.matrix[1][0] = 2;
//     eq.matrix[1][1] = 4;

//     int equal = s21_eq_matrix(&res, &eq);
//   s21_print(&eq);
// }