#include "s21_test.h"

START_TEST(test_1) {
  char str1[] = "Hello, are you.looking at!my code?";
  char str2[] = "Hello, are you.looking at!my code?";
  const char delim[] = " ,!.?";

  char *token = strtok(str1, delim);
  char *my_token = s21_strtok(str2, delim);

  while (token != NULL || my_token != S21_NULL) {
    ck_assert_msg((token == NULL) == (my_token == S21_NULL),
                  "One of the tokens is NULL");
    if (token && my_token) ck_assert_str_eq(token, my_token);
    token = strtok(NULL, delim);
    my_token = s21_strtok(S21_NULL, delim);
  }
}
END_TEST

START_TEST(test_2) {
  char str1[] = "Hello,,,,are you.looking at!my code?";
  char str2[] = "Hello,,,,are you.looking at!my code?";
  const char delim[] = "?,. ";

  char *token = strtok(str1, delim);
  char *my_token = s21_strtok(str2, delim);

  while (token != NULL || my_token != S21_NULL) {
    ck_assert_msg((token == NULL) == (my_token == S21_NULL),
                  "One of the tokens is NULL");
    if (token && my_token) ck_assert_str_eq(token, my_token);
    token = strtok(NULL, delim);
    my_token = s21_strtok(S21_NULL, delim);
  }
}
END_TEST

START_TEST(test_3) {
  char str1[] = "??, .t!?";
  char str2[] = "??, .t!?";
  const char delim[] = " ,!.?";

  char *token = strtok(str1, delim);
  char *my_token = s21_strtok(str2, delim);

  while (token != NULL || my_token != S21_NULL) {
    ck_assert_msg((token == NULL) == (my_token == S21_NULL),
                  "One of the tokens is NULL");
    if (token && my_token) ck_assert_str_eq(token, my_token);
    token = strtok(NULL, delim);
    my_token = s21_strtok(S21_NULL, delim);
  }
}
END_TEST

START_TEST(test_4) {
  char str1[] = "";
  char str2[] = "";
  const char delim[] = " ,!.?";

  char *token = strtok(str1, delim);
  char *my_token = s21_strtok(str2, delim);

  while (token != NULL || my_token != S21_NULL) {
    ck_assert_msg((token == NULL) == (my_token == S21_NULL),
                  "One of the tokens is NULL");
    if (token && my_token) ck_assert_str_eq(token, my_token);
    token = strtok(NULL, delim);
    my_token = s21_strtok(S21_NULL, delim);
  }
}
END_TEST

START_TEST(test_5) {
  char str1[] = "Text_without_delimiters";
  char str2[] = "Text_without_delimiters";
  const char delim[] = " ,!.?";

  char *token = strtok(str1, delim);
  char *my_token = s21_strtok(str2, delim);

  while (token != NULL || my_token != S21_NULL) {
    ck_assert_msg((token == NULL) == (my_token == S21_NULL),
                  "One of the tokens is NULL");
    if (token && my_token) ck_assert_str_eq(token, my_token);
    token = strtok(NULL, delim);
    my_token = s21_strtok(S21_NULL, delim);
  }
}
END_TEST

Suite *suite_strtok(void) {
  Suite *suite = suite_create("TEST STRTOK");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  suite_add_tcase(suite, test_case);
  return suite;
}