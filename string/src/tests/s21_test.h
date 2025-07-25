#ifndef S21_TEST
#define S21_TEST

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// String test functions
Suite* suite_memchr(void);
Suite* suite_memcmp(void);
Suite* suite_memcpy(void);
Suite* suite_memset(void);
Suite* suite_strchr(void);
Suite* suite_strrchr(void);
Suite* suite_strncat(void);
Suite* suite_strlen(void);
Suite* suite_strncpy(void);
Suite* suite_strcspn(void);
Suite* suite_strncmp(void);
Suite* suite_strerror(void);
Suite* suite_strstr(void);
Suite* suite_strpbrk(void);
Suite* suite_strtok(void);
// Addition test functions
Suite* suite_to_lower(void);
Suite* suite_to_upper(void);
Suite* suite_to_insert(void);
Suite* suite_trim(void);
// Sprintf modifier test functions
Suite* suite_sprintf_d(void);
Suite* suite_sprintf_c(void);
Suite* suite_sprintf_s(void);
Suite* suite_sprintf_f(void);
Suite* suite_sprintf_u(void);
#endif