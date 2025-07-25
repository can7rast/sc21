#include "s21_test.h"

START_TEST(test_1) {
  const char string_part[] = "  aaaaaI Love Tatarstanbbbb  ";
  const char string_true[] = "I Love Tatarstan";
  const char string_trim_chars[] = " ab";
  char *string_new = s21_trim(string_part, string_trim_chars);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

START_TEST(test_2) {
  const char string_part[] = "";
  const char *string_true = S21_NULL;
  const char string_trim_chars[] = "ab";
  char *string_new = s21_trim(string_part, string_trim_chars);
  ck_assert_ptr_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

START_TEST(test_3) {
  const char string_part[] = "aaaaaI Love Tatarstanbbbba";
  const char string_true[] = "I Love Tatarstanbbbb";
  const char string_trim_chars[] = "a";
  char *string_new = s21_trim(string_part, string_trim_chars);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

START_TEST(test_4) {
  const char string_part[] = "    ";
  const char string_true[] = "";
  const char string_trim_chars[] = " ";
  char *string_new = s21_trim(string_part, string_trim_chars);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

Suite *suite_trim(void) {
  Suite *suite = suite_create("TEST TRIM");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  suite_add_tcase(suite, test_case);
  return suite;
}