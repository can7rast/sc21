#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_fill_matrix(matrix_t *res);

void s21_free_matrix(matrix_t *res);
void s21_remove_matrix(matrix_t *A);

int s21_eq_size(matrix_t *A, matrix_t *B);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_exist_matrix(matrix_t *A);
int s21_check_matrix(matrix_t *A, matrix_t *B, matrix_t *res);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_m_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);

void s21_based_minor(matrix_t *A, double *result);
int s21_fill_minor(int k, int z, matrix_t *A, matrix_t *B);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

matrix_t s21_create_test_matrix(int rows, int columns);
void s21_fill(matrix_t *m, double start_val);

#define MAXDOUBLE DBL_MAX

#endif