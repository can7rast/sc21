#include "s21_test.h"

START_TEST(test_1) {
  const char string1[] = "I love Tatarstan";
  const char string2[] = "I love Tatarstan";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(string1, string2, n),
                   strncmp(string1, string2, n));
}
END_TEST

START_TEST(test_2) {
  const char string1[] = "I love Tatarstan";
  const char string2[] = "I love Tatarstan";
  size_t n = 0;
  ck_assert_int_eq(s21_strncmp(string1, string2, n),
                   strncmp(string1, string2, n));
}
END_TEST

START_TEST(test_3) {
  const char string1[] = "I love Tatarstan";
  const char string2[] = "I love Tatarstan";
  size_t n = 10;
  ck_assert_int_eq(s21_strncmp(string1, string2, n),
                   strncmp(string1, string2, n));
}
END_TEST

START_TEST(test_4) {
  const char string1[] = "I love Tatarstan";
  const char string2[] = "I love Tatarstan";
  size_t n = 1;
  ck_assert_int_eq(s21_strncmp(string1, string2, n),
                   strncmp(string1, string2, n));
}
END_TEST

START_TEST(test_5) {
  const char string1[] = "I love Tatarstan";
  const char string2[] = "I love TatarstaN";
  size_t n = 16;
  ck_assert_int_eq(s21_strncmp(string1, string2, n),
                   strncmp(string1, string2, n));
}
END_TEST

Suite *suite_strncmp(void) {
  Suite *suite = suite_create("TEST STRNCMP");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}