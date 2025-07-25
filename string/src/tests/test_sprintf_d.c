#include "s21_test.h"

START_TEST(test_1) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%d", 123);
  s21_sprintf(buffer2, "%d", 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_2) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%d", -123);
  s21_sprintf(buffer2, "%d", -123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_3) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%-5d", -123);
  s21_sprintf(buffer2, "%-5d", -123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_4) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%+-6d", 123);
  s21_sprintf(buffer2, "%+-6d", 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_5) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%05d", 123);
  s21_sprintf(buffer2, "%05d", 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_6) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%+05d", 123);
  s21_sprintf(buffer2, "%+05d", 123);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *suite_sprintf_d(void) {
  Suite *suite = suite_create("TEST SPECIFIER_D");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  tcase_add_test(test_case, test_6);
  suite_add_tcase(suite, test_case);
  return suite;
}
