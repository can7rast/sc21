#include "s21_test.h"

START_TEST(test_1) {
  char string_1[] = "testing";
  const char string_2[] = "progress..";
  s21_size_t n = 5;
  char *ans_1 = s21_strncpy(string_1, string_2, n),
       *ans_2 = strncpy(string_1, string_2, n);
  ck_assert_str_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_2) {
  char string_1[50] = "testing";
  const char string_2[] = "progress..";
  s21_size_t n = s21_strlen(string_2);
  char *ans_1 = s21_strncpy(string_1, string_2, n),
       *ans_2 = strncpy(string_1, string_2, n);
  ck_assert_str_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_3) {
  char string_1[] = "testing";
  const char string_2[] = "";
  s21_size_t n = 5;
  char *ans_1 = s21_strncpy(string_1, string_2, n),
       *ans_2 = strncpy(string_1, string_2, n);
  ck_assert_str_eq(ans_1, ans_2);
}
END_TEST
Suite* suite_strncat(void) {
  Suite* suite = suite_create("TEST STRNCAT");
  TCase* test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);

  suite_add_tcase(suite, test_case);
  return suite;
}