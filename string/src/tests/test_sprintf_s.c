#include "s21_test.h"

START_TEST(test_1) {
  char buffer1[200], buffer2[200];
  char pattern[] = "hello";
  sprintf(buffer1, "%s", pattern);
  s21_sprintf(buffer2, "%s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_2) {
  char buffer1[200], buffer2[200];
  char pattern[] = "hello";
  sprintf(buffer1, "%10s", pattern);
  s21_sprintf(buffer2, "%10s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_3) {
  char buffer1[200], buffer2[200];
  char pattern[] = "hello";
  sprintf(buffer1, "%-15s", pattern);
  s21_sprintf(buffer2, "%-15s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_4) {
  char buffer1[200], buffer2[200];
  char pattern[] = "school";
  sprintf(buffer1, "%.3s", pattern);
  s21_sprintf(buffer2, "%.3s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_5) {
  char buffer1[200], buffer2[200];
  char pattern[] = "school";
  sprintf(buffer1, "%.10s", pattern);
  s21_sprintf(buffer2, "%.10s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_6) {
  char buffer1[200], buffer2[200];
  char pattern[] = "school";
  sprintf(buffer1, "%10.3s", pattern);
  s21_sprintf(buffer2, "%10.3s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_7) {
  char buffer1[200], buffer2[200];
  char pattern[] = "Tatarstan";
  sprintf(buffer1, "%-9.4s", pattern);
  s21_sprintf(buffer2, "%-9.4s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_8) {
  char buffer1[200], buffer2[200];
  char *pattern = "";
  sprintf(buffer1, "%s", pattern);
  s21_sprintf(buffer2, "%s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_9) {
  char buffer1[200], buffer2[200];
  sprintf(buffer1, "%5s", "");
  s21_sprintf(buffer2, "%5s", "");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_10) {
  char buffer1[200], buffer2[200];
  char pattern[] = "Tatarstan";
  sprintf(buffer1, "%.0s", pattern);
  s21_sprintf(buffer2, "%.0s", pattern);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *suite_sprintf_s(void) {
  Suite *suite = suite_create("TEST SPECIFIER_S");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  tcase_add_test(test_case, test_6);
  tcase_add_test(test_case, test_7);
  tcase_add_test(test_case, test_8);
  tcase_add_test(test_case, test_9);
  tcase_add_test(test_case, test_10);
  suite_add_tcase(suite, test_case);
  return suite;
}