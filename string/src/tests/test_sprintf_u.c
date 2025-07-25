#include "s21_test.h"

START_TEST(test_1) {
  char buffer1[200], buffer2[200];
  unsigned num = 5646161;
  sprintf(buffer1, "%020u", num);
  s21_sprintf(buffer2, "%020d", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_2) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%20.u", num);
  s21_sprintf(buffer2, "%20.u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_3) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%20.u", num);
  s21_sprintf(buffer2, "%20.u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_4) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%-20.u", num);
  s21_sprintf(buffer2, "%-20.u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_5) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%u", num);
  s21_sprintf(buffer2, "%u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_6) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%.u", num);
  s21_sprintf(buffer2, "%.u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_7) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%.20u", num);
  s21_sprintf(buffer2, "%.20u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_8) {
  char buffer1[200], buffer2[200];
  unsigned int num = 2142;
  sprintf(buffer1, "%19.20u", num);
  s21_sprintf(buffer2, "%19.20u", num);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *suite_sprintf_u(void) {
  Suite *suite = suite_create("TEST SPECIFIER_U");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  tcase_add_test(test_case, test_6);
  tcase_add_test(test_case, test_7);
  tcase_add_test(test_case, test_8);
  suite_add_tcase(suite, test_case);
  return suite;
}