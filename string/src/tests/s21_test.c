#include "s21_test.h"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"

int main() {
  // Все что связано с strings
  SRunner *runner = srunner_create(suite_memcmp());
  srunner_add_suite(runner, suite_memchr());
  srunner_add_suite(runner, suite_memcpy());
  srunner_add_suite(runner, suite_memset());
  srunner_add_suite(runner, suite_strchr());
  srunner_add_suite(runner, suite_strrchr());
  srunner_add_suite(runner, suite_strlen());
  srunner_add_suite(runner, suite_strncat());
  srunner_add_suite(runner, suite_strncpy());
  srunner_add_suite(runner, suite_strcspn());
  srunner_add_suite(runner, suite_strncmp());
  srunner_add_suite(runner, suite_strerror());
  srunner_add_suite(runner, suite_strstr());
  srunner_add_suite(runner, suite_strpbrk());
  srunner_add_suite(runner, suite_strtok());
  srunner_add_suite(runner, suite_sprintf_f());
  srunner_run_all(runner, CK_NORMAL);
  int number_failed_strings = srunner_ntests_failed(runner);
  int number_tests_strings = srunner_ntests_run(runner);
  // Все что связано с допами;
  SRunner *runner_add_parts = srunner_create(suite_to_lower());
  srunner_add_suite(runner_add_parts, suite_to_upper());
  srunner_add_suite(runner_add_parts, suite_to_insert());
  srunner_add_suite(runner_add_parts, suite_trim());
  srunner_run_all(runner_add_parts, CK_NORMAL);
  int number_failed_add_parts = srunner_ntests_failed(runner_add_parts);
  int number_tests_add_parts = srunner_ntests_run(runner_add_parts);

  SRunner *runner_sprintf = srunner_create(suite_sprintf_d());
  srunner_add_suite(runner_sprintf, suite_sprintf_f());
  srunner_add_suite(runner_sprintf, suite_sprintf_u());
  srunner_add_suite(runner_sprintf, suite_sprintf_s());
  srunner_add_suite(runner_sprintf, suite_sprintf_c());

  srunner_run_all(runner_sprintf, CK_NORMAL);

  int number_failed_sprintf = srunner_ntests_failed(runner_sprintf);
  int number_tests_sprintf = srunner_ntests_run(runner_sprintf);

  int all_tests =
      number_tests_add_parts + number_tests_strings + number_tests_sprintf;
  printf("\n" GREEN "===TESTS RESULT===" RESET "\n\n");
  printf(GREEN "Total tests: %d" RESET "\n\n", all_tests);
  if (number_failed_strings > 0) {
    printf(RED "Failed with errors in stings: %d" RESET "\n\n",
           number_failed_strings);
  } else {
    printf(GREEN "All strings tests successfully!" RESET "\n\n");
  }
  if (number_failed_add_parts > 0) {
    printf(RED "Failed with errors in additional parts: %d" RESET "\n\n",
           number_failed_add_parts);
  } else {
    printf(GREEN "All additional parts tests successfully!" RESET "\n\n");
  }
  if (number_failed_sprintf > 0) {
    printf(RED "Failed with errors in sprintf: %d" RESET "\n\n",
           number_failed_sprintf);
  } else {
    printf(GREEN "All sprintf modifier tests successfully!" RESET "\n\n");
  }
  srunner_free(runner);
  srunner_free(runner_add_parts);
  srunner_free(runner_sprintf);
  return 0;
}