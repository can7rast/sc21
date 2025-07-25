#include "s21_test.h"

START_TEST(test_1) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "hello %c", 'c');
  s21_sprintf(buffer2, "hello %c", 'c');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_2) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "hello %5c", 'D');
  s21_sprintf(buffer2, "hello %5c", 'D');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_3) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "hello %-10c", 'f');
  s21_sprintf(buffer2, "hello %-10c", 'f');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_4) {
  int num = 65;
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "hello %c", num);
  s21_sprintf(buffer2, "hello %c", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_5) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "|%-10c|%5c|", 'a', 'b');
  s21_sprintf(buffer2, "|%-10c|%5c|", 'a', 'b');
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *suite_sprintf_c(void) {
  Suite *suite = suite_create("TEST SPECIFIER_C");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  suite_add_tcase(suite, test_case);
  return suite;
}