#include "s21_test.h"

START_TEST(test_1) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  int Char = 'P';
  size_t n = 5;
  ck_assert_str_eq(s21_memset(string_1, Char, n), memset(string_2, Char, n));
}
END_TEST

START_TEST(test_2) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  int Char = 'I';
  size_t n = 0;
  ck_assert_str_eq(s21_memset(string_1, Char, n), memset(string_2, Char, n));
}
END_TEST

START_TEST(test_3) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  int Char = 'I';
  size_t n = 10;
  ck_assert_str_eq(s21_memset(string_1, Char, n), memset(string_2, Char, n));
}
END_TEST

START_TEST(test_4) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  int Char = '\0';
  size_t n = 5;
  ck_assert_str_eq(s21_memset(string_1, Char, n), memset(string_2, Char, n));
}
END_TEST

START_TEST(test_5) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  int Char = 's';
  size_t n = 5;
  ck_assert_str_eq(s21_memset(string_1, Char, n), memset(string_2, Char, n));
}
END_TEST
Suite *suite_memset(void) {
  Suite *suite = suite_create("TEST MEMSET");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}