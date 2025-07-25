#include "tests.h"

// Тест 1: Успешное вычитание матриц
START_TEST(test1) {
  matrix_t A = s21_create_test_matrix(2, 2);
  matrix_t B = s21_create_test_matrix(2, 2);
  matrix_t result;
  s21_fill(&A, 1.0);  // A = [[1, 2], [3, 4]]
  s21_fill(&B, 2.0);  // B = [[2, 3], [4, 5]]

  int error = s21_sub_matrix(&B, &A, &result);
  matrix_t equal = s21_create_test_matrix(2, 2);
  equal.matrix[0][0] = 1.0;
  equal.matrix[0][1] = 1.0;
  equal.matrix[1][0] = 1.0;
  equal.matrix[1][1] = 1.0;

  int eq = s21_eq_matrix(&result, &equal);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&equal);
}
END_TEST

// Тест 2: Некорректные входные данные (NULL)
START_TEST(test_sub_matrix_null) {
  matrix_t A = s21_create_test_matrix(2, 2);
  matrix_t result;
  int error = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(error, 1);
  error = s21_sub_matrix(NULL, &A, &result);
  ck_assert_int_eq(error, 1);
  error = s21_sub_matrix(&A, &A, NULL);
  ck_assert_int_eq(error, 1);
  s21_remove_matrix(&A);
}
END_TEST

// Тест 3: Матрицы разного размера
START_TEST(test_sub_matrix_different_size) {
  matrix_t A = s21_create_test_matrix(2, 2);
  matrix_t B = s21_create_test_matrix(2, 3);
  s21_fill(&A, 1);
  s21_fill(&B, 5);
  matrix_t result;
  int error = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(error, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 4: Сложение с бесконечностью
START_TEST(test_sub_matrix_infinity) {
  matrix_t A = s21_create_test_matrix(2, 2);
  matrix_t B = s21_create_test_matrix(2, 2);
  matrix_t result;
  s21_fill(&A, 1.0);
  s21_fill(&B, 1.0);
  A.matrix[0][0] = 1.0 / 0.0;  // Установка INF
  int error = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(error, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Минимальный размер матрицы (1x1)
START_TEST(test_sub_matrix_min_size) {
  matrix_t A = s21_create_test_matrix(1, 1);
  matrix_t B = s21_create_test_matrix(1, 1);
  matrix_t result;
  A.matrix[0][0] = 5.0;
  B.matrix[0][0] = 3.0;
  int error = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq(result.matrix[0][0], 2.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test6) {
  matrix_t res = {};
  int error = s21_sub_matrix(NULL, NULL, &res);
  ck_assert_int_eq(error, 1);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_sub_matrix_test(void) {
  Suite *s = suite_create("s21_sub_matrix");
  TCase *tc = tcase_create("t21_sub_matrix");
  tcase_add_test(tc, test1);
  tcase_add_test(tc, test_sub_matrix_null);
  tcase_add_test(tc, test_sub_matrix_different_size);
  tcase_add_test(tc, test_sub_matrix_infinity);
  tcase_add_test(tc, test_sub_matrix_min_size);
  tcase_add_test(tc, test6);

  suite_add_tcase(s, tc);

  return s;
}