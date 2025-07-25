#include "s21_test.h"

START_TEST(test_1) {
  const char string_true[] = "I love Tatarstan";
  const char string_part[] = "I  Tatarstan";
  const char string_insert[] = "love";
  s21_size_t index = 2;
  char *string_new1 = s21_insert(string_part, string_insert, index);
  ck_assert_str_eq(string_new1, string_true);
  if (string_new1 != S21_NULL) free(string_new1);
}
END_TEST

START_TEST(test_2) {
  const char string_true[] = "I love";
  const char string_part[] = "I ";
  const char string_insert[] = "love";
  s21_size_t index = 2;
  char *string_new2 = s21_insert(string_part, string_insert, index);
  ck_assert_str_eq(string_new2, string_true);
  if (string_new2 != S21_NULL) free(string_new2);
}
END_TEST

START_TEST(test_3) {
  const char string_true[] = "I love Tatarstan";
  const char string_part[] = "";
  const char string_insert[] = "I love Tatarstan";
  s21_size_t index = 0;
  char *string_new3 = s21_insert(string_part, string_insert, index);
  ck_assert_str_eq(string_new3, string_true);
  if (string_new3 != S21_NULL) free(string_new3);
}
END_TEST

START_TEST(test_4) {
  const char string_true[] = "I love Tatarstan  ";
  const char string_part[] = "I love Tatarstan ";
  const char string_insert[] = " ";
  s21_size_t index = s21_strlen(string_part) - 1;
  char *string_new4 = s21_insert(string_part, string_insert, index);
  ck_assert_str_eq(string_new4, string_true);
  if (string_new4 != S21_NULL) free(string_new4);
}
END_TEST

Suite *suite_to_insert(void) {
  Suite *suite = suite_create("TEST TO_INSERT");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  suite_add_tcase(suite, test_case);
  return suite;
}