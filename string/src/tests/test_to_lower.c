#include "s21_test.h"

START_TEST(test_1) {
  const char string_true[] = "i love tatarstan";
  const char string_part[] = "I LOVE TATARSTAN";
  char *string_new = s21_to_lower(string_part);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

START_TEST(test_2) {
  const char string_true[] = "i love tatarstan";
  const char string_part[] = "I LoVe tatARSTAN";
  char *string_new = s21_to_lower(string_part);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

START_TEST(test_3) {
  const char string_true[] = "tat";
  const char string_part[] = "tat";
  char *string_new = s21_to_lower(string_part);
  ck_assert_str_eq(string_new, string_true);
  if (string_new != S21_NULL) free(string_new);
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *suite = suite_create("TEST TO_LOWER");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  suite_add_tcase(suite, test_case);
  return suite;
}