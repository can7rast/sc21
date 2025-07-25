#include "s21_test.h"

START_TEST(test_1) {
  const char string[] = "I love Tatarstan";
  const char Char[] = "o";
  ck_assert_int_eq(s21_strcspn(string, Char), strcspn(string, Char));
}
END_TEST

START_TEST(test_2) {
  const char string[] = "I love Tatarstan";
  const char Char[] = "n";
  ck_assert_int_eq(s21_strcspn(string, Char), strcspn(string, Char));
}
END_TEST

START_TEST(test_3) {
  const char string[] = "I love Tatarstan";
  const char Char[] = "love";
  ck_assert_int_eq(s21_strcspn(string, Char), strcspn(string, Char));
}
END_TEST

START_TEST(test_4) {
  const char string[] = "I love Tatarstan";
  const char Char[] = "s";
  ck_assert_int_eq(s21_strcspn(string, Char), strcspn(string, Char));
}
END_TEST

START_TEST(test_5) {
  const char string[] = "I love Tatarstan";
  const char Char[] = "";
  ck_assert_int_eq(s21_strcspn(string, Char), strcspn(string, Char));
}
END_TEST

Suite *suite_strcspn(void) {
  Suite *suite = suite_create("TEST STRCSPN");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}