#include "s21_test.h"

START_TEST(test_1) {
  char string[] = "I love Tatarstan";
  int Char = 'o';
  size_t n = 5;
  ck_assert_pstr_eq(s21_memchr(string, Char, n), memchr(string, Char, n));
}
END_TEST

START_TEST(test_2) {
  char string[] = "I love Tatarstan";
  int Char = 'o';
  size_t n = 0;
  ck_assert_pstr_eq(s21_memchr(string, Char, n), memchr(string, Char, n));
}
END_TEST

START_TEST(test_3) {
  char string[] = "I love Tatarstan";
  int Char = 'o';
  size_t n = 10;
  ck_assert_pstr_eq(s21_memchr(string, Char, n), memchr(string, Char, n));
}
END_TEST

START_TEST(test_4) {
  char string[] = "I love Tatarstan";
  int Char = '\0';
  size_t n = 5;
  ck_assert_pstr_eq(s21_memchr(string, Char, n), memchr(string, Char, n));
}
END_TEST

START_TEST(test_5) {
  char string[] = "I love Tatarstan";
  int Char = 's';
  size_t n = 5;
  ck_assert_pstr_eq(s21_memchr(string, Char, n), memchr(string, Char, n));
}
END_TEST

Suite *suite_memchr(void) {
  Suite *suite = suite_create("TEST MEMCHR");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}