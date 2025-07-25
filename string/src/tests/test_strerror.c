#include "s21_test.h"

START_TEST(test_1) {
  int n = 0;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(test_2) {
  int n = 17;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(test_3) {
  int n = 30;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(test_4) {
  int n = 100;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(test_5) {
  int n = 200;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST
Suite *suite_strerror(void) {
  Suite *suite = suite_create("TEST STRERROR");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  suite_add_tcase(suite, test_case);
  return suite;
}
