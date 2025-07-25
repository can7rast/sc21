#include "s21_test.h"

START_TEST(test_1) {
  const char string_1[] = "I love Tatarstan";
  const char string_2[] = "I love Russia";
  size_t n = 5;
  int ans_1 = s21_memcmp(string_1, string_2, n),
      ans_2 = memcmp(string_1, string_2, n);
  ck_assert_int_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_2) {
  const char string_1[] = "I love Tatarstan";
  const char string_2[] = "I love Russia";
  size_t n = 5;
  int ans_1 = s21_memcmp(string_1, string_2, n),
      ans_2 = memcmp(string_1, string_2, n);
  ck_assert_int_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_3) {
  const char string_1[] = "I love Tatarstan";
  const char string_2[] = "I'm man";
  size_t n = 0;
  int ans_1 = s21_memcmp(string_1, string_2, n),
      ans_2 = memcmp(string_1, string_2, n);
  ck_assert_int_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_4) {
  const char string_1[] = "Old World";
  const char string_2[] = "New World";
  size_t n = 5;
  int ans_1 = s21_memcmp(string_1, string_2, n),
      ans_2 = memcmp(string_1, string_2, n);
  ck_assert_int_eq(ans_1, ans_2);
}
END_TEST

START_TEST(test_5) {
  const char string_1[] = "MEMCPY";
  const char string_2[] = "MEMCMP";
  size_t n = 4;
  int ans_1 = s21_memcmp(string_1, string_2, n),
      ans_2 = memcmp(string_1, string_2, n);
  ck_assert_int_eq(ans_1, ans_2);
}
END_TEST
Suite *suite_memcmp(void) {
  Suite *suite = suite_create("TEST MEMCMP");
  TCase *test_case = tcase_create("TEST CASE");
  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}