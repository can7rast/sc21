#include "../s21_matrix.h"

matrix_t s21_create_test_matrix(int rows, int columns) {
  matrix_t m;
  s21_create_matrix(rows, columns, &m);
  return m;
}

void s21_fill(matrix_t *m, double start_val) {
  double val = start_val;
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->columns; j++) {
      m->matrix[i][j] = val++;
    }
  }
}
