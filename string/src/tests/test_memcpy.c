#include "s21_test.h"

START_TEST(test_1) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  const char src[] = "World";
  size_t n = 5;
  ck_assert_str_eq(s21_memcpy(string_1, src, n), memcpy(string_2, src, n));
}
END_TEST

START_TEST(test_2) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  const char src[] = "World";
  size_t n = 4;
  ck_assert_str_eq(s21_memcpy(string_1, src, n), memcpy(string_2, src, n));
}
END_TEST

START_TEST(test_3) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  const char src[] = "World";
  size_t n = 3;
  ck_assert_str_eq(s21_memcpy(string_1, src, n), memcpy(string_2, src, n));
}
END_TEST

START_TEST(test_4) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  const char src[] = "Russia";
  size_t n = 5;
  ck_assert_str_eq(s21_memcpy(string_1, src, n), memcpy(string_2, src, n));
}
END_TEST

START_TEST(test_5) {
  char string_1[] = "I love Tatarstan";
  char string_2[] = "I love Tatarstan";
  const char src[] = "World";
  size_t n = 5;
  ck_assert_str_eq(s21_memcpy(string_1, src, n), memcpy(string_2, src, n));
}
END_TEST
Suite *suite_memcpy(void) {
  Suite *suite = suite_create("TEST MEMCPY");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}