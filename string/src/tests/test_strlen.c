#include "s21_test.h"

START_TEST(test_1) {
  const char string_1[] = "Testing progress...";
  s21_size_t ans_1 = s21_strlen(string_1), ans_2 = s21_strlen(string_1);
  ck_assert_uint_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_2) {
  const char string_1[] = "Testing progress..";
  s21_size_t ans_1 = s21_strlen(string_1), ans_2 = s21_strlen(string_1);
  ck_assert_uint_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_3) {
  const char string_1[] = "NULL";
  s21_size_t ans_1 = s21_strlen(string_1), ans_2 = s21_strlen(string_1);
  ck_assert_uint_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_4) {
  const char string_1[] = "";
  s21_size_t ans_1 = s21_strlen(string_1), ans_2 = s21_strlen(string_1);
  ck_assert_uint_eq(ans_1, ans_2);
}
END_TEST
Suite *suite_strlen(void) {
  Suite *suite = suite_create("TEST STRLEN");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);

  suite_add_tcase(suite, test_case);
  return suite;
}