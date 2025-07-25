#include "s21_test.h"

START_TEST(test_1) {
  char string_1[200], string_2[200];
  const char *format = "[%.6f + %12f]";
  double number_1 = 1.23345, number_2 = 1234.12345;
  sprintf(string_1, format, number_1, number_2);
  s21_sprintf(string_2, format, number_1, number_2);
  ck_assert_str_eq(string_1, string_2);
}
END_TEST

START_TEST(test_2) {
  char string_1[200], string_2[200];
  const char *format = "[%+.0f + %01.5f]";
  double number_1 = 1.23345, number_2 = 1234.12345;
  sprintf(string_1, format, number_1, number_2);
  s21_sprintf(string_2, format, number_1, number_2);
  ck_assert_str_eq(string_1, string_2);
}
END_TEST

START_TEST(test_3) {
  char string_1[200], string_2[200];
  const char *format = "[%-12.2f + %+-12.3f]";
  double number_1 = 1.23345, number_2 = 1234.12345;
  sprintf(string_1, format, number_1, number_2);
  s21_sprintf(string_2, format, number_1, number_2);
  ck_assert_str_eq(string_1, string_2);
}
END_TEST

START_TEST(test_4) {
  char string_1[200], string_2[200];
  const char *format = "[%-+12f + %  01.2f]";
  double number_1 = 1.23345, number_2 = 1234.12345;
  sprintf(string_1, format, number_1, number_2);
  s21_sprintf(string_2, format, number_1, number_2);
  ck_assert_str_eq(string_1, string_2);
}
END_TEST

START_TEST(test_5) {
  char string_1[200], string_2[200];
  const char *format = "[%.0f + % 012f]";
  double number_1 = 1.23345, number_2 = 1234.12345;
  sprintf(string_1, format, number_1, number_2);
  s21_sprintf(string_2, format, number_1, number_2);
  ck_assert_str_eq(string_1, string_2);
}
END_TEST
Suite *suite_sprintf_f(void) {
  Suite *suite = suite_create("TEST SPRINTF_F");
  TCase *test_case = tcase_create("TEST CASE SPRTINF_F");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}