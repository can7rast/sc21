#ifndef s21_string
#define s21_string

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define S21_NULL (void *)0
typedef unsigned long s21_size_t;

struct flags {
  int zero;
  int plus;
  int minus;
  int space;
  int lat;
};

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void s21_int_to_string(char *str, int n);
int convert_str_in_int(const char *format, int *pos_format);
char *convert_size_t_in_str(s21_size_t number);
void parser_flags(char c, struct flags *flag);
char *parser_value(char *buffer, const char *format, int *pos_format,
                   int *pos_buffer, va_list *args);
int s21_sprintf(char *buffer, const char *format, ...);
int s21_sprintf_c(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, va_list *args);
int s21_sprintf_s(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, int length, va_list *args);
int s21_sprintf_d(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, va_list *args);
int s21_sprintf_f(char *buffer, int *pos_buffer, int width, struct flags *flag,
                  int length, va_list *args);
int s21_sprintf_u(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, int length, va_list *args);
#endif