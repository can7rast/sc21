#include "s21_test.h"

START_TEST(test_1) {
  const char *str1 = "Hello my name is";
  const char *str2 = "mi";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

START_TEST(test_2) {
  const char *str1 = "Hello my name is";
  const char *str2 = "no";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

START_TEST(test_3) {
  const char *str1 = "Hello my name is";
  const char *str2 = "qwzx";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

START_TEST(test_4) {
  const char *str1 = "";
  const char *str2 = "";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

START_TEST(test_5) {
  const char *str1 = "";
  const char *str2 = "no";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

START_TEST(test_6) {
  const char *str1 = "hello";
  const char *str2 = "";

  char *result = strpbrk(str1, str2);
  char *my_result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, my_result);
}
END_TEST

Suite *suite_strpbrk(void) {
  Suite *suite = suite_create("TEST STRPBRK");
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