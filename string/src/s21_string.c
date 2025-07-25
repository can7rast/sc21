#include "s21_string.h"

#include <stdlib.h>

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int answer = 0;
  if (str1 == S21_NULL || str2 == S21_NULL) {
    printf("The pointer is NULL\n");
  } else {
    const unsigned char *bites1 = (const unsigned char *)str1;
    const unsigned char *bites2 = (const unsigned char *)str2;
    for (s21_size_t i = 0; i < n && answer == 0; i++) {
      if (bites1[i] < bites2[i])
        answer = bites1[i] - bites2[i];
      else if (bites1[i] > bites2[i])
        answer = bites1[i] - bites2[i];
    }
  }
  return answer;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) {
    printf("The pointer is NULL\n");
  } else {
    unsigned char *dest_bites = (unsigned char *)dest;
    const unsigned char *src_bites = (unsigned char *)src;

    if (src_bites < dest_bites)
      for (s21_size_t i = n; i > (s21_size_t)0; i--)
        dest_bites[i - 1] = src_bites[i - 1];
    else
      for (s21_size_t i = 0; i < n; i++) dest_bites[i] = src_bites[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == S21_NULL) {
    printf("The pointer is NULL\n");
  } else {
    unsigned char *str_bites = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) str_bites[i] = c;
  }
  return str;
}

char *s21_strchr(const char *str, int c) {
  char *answer = S21_NULL;
  if (str != S21_NULL) {
    if (c == '\0') answer = (char *)str + s21_strlen(str);
    for (s21_size_t i = 0; str[i] != '\0' && answer == S21_NULL; i++)
      if (str[i] == c) answer = (char *)str + i;
  }
  return answer;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;

  if (str1 == S21_NULL || str2 == S21_NULL) {
    printf("The pointer is NULL\n");
    result = -1;
  } else {
    while (i < n && result == 0) {
      if (str1[i] == '\0' && str2[i] == '\0') {
        result = 0;
      } else if (str1[i] == '\0') {
        result = -1;
      } else if (str2[i] == '\0') {
        result = 1;
      } else if (str1[i] != str2[i]) {
        result = (unsigned char)str1[i] - (unsigned char)str2[i];
      }
      i++;
    }
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *answer = S21_NULL;

  if (str != S21_NULL) {
    for (s21_size_t i = 0; str[i] != '\0' || (unsigned char)c == '\0'; i++) {
      if ((unsigned char)str[i] == (unsigned char)c) {
        answer = (char *)str + i;
      }
    }
  }

  return answer;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t len_frs = s21_strlen(dest);
    s21_size_t i = 0;
    while (i < n && src[i] != '\0') {
      dest[len_frs + i] = src[i];
      i++;
    }
    dest[len_frs + i] = '\0';
  }
  return dest;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != S21_NULL) {
    while (str[len] != '\0') {
      len++;
    }
  }
  return len;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
      dest[i] = src[i];
      dest[i + 1] = '\0';
    }
  }
  return dest;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int flag = 0;

  if (*needle == '\0') {
    result = (char *)haystack;
    flag = 1;
  }

  char *temp_haystack, *temp_needle;
  while (*haystack && !flag) {
    if (*haystack == *needle) {
      temp_haystack = (char *)haystack;
      temp_needle = (char *)needle;

      while (*temp_haystack && *temp_needle && *temp_haystack == *temp_needle) {
        temp_haystack++;
        temp_needle++;
      }

      if (*temp_needle == '\0') {
        result = (char *)haystack;
        flag = 1;
      }
    }
    haystack++;
  }

  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int flag = 0;

  while (*str1 && !flag) {
    for (const char *p = str2; *p != '\0' && !flag; p++) {
      if (*str1 == *p) {
        result = (char *)str1;
        flag = 1;
      }
    }
    str1++;
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *cur_pos = S21_NULL;
  char *result = S21_NULL;

  if (str) cur_pos = str;

  if (cur_pos) {
    while (*cur_pos && s21_strchr(delim, *cur_pos)) cur_pos++;
    if (*cur_pos) {
      result = cur_pos;

      while (*cur_pos && !s21_strchr(delim, *cur_pos)) cur_pos++;

      if (*cur_pos) {
        *cur_pos = '\0';
        cur_pos++;
      }
    }
  }

  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = S21_NULL;
  if (str == S21_NULL) {
    printf("The pointer is NULL\n");
  } else {
    const unsigned char *bites = (const unsigned char *)str;
    for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
      if (bites[i] == c) {
        result = (void *)(bites + i);
      }
    }
  }
  return result;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  if (str1 != NULL && str2 != NULL) {
    int found = 0;

    while (str1[result] != '\0' && !found) {
      for (s21_size_t i = 0; str2[i] != '\0' && !found; i++) {
        if (str1[result] == str2[i]) {
          found = 1;
        }
      }
      if (!found) {
        result++;
      }
    }
  } else {
    printf("The pointer is NULL\n");
  }

  return result;
}

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

const char *maserror[] = {"Undefined error: 0",
                          "Operation not permitted",
                          "No such file or directory",
                          "No such process",
                          "Interrupted system call",
                          "Input/output error",
                          "Device not configured",
                          "Argument list too long",
                          "Exec format error",
                          "Bad file descriptor",
                          "No child processes",
                          "Resource deadlock avoided",
                          "Cannot allocate memory",
                          "Permission denied",
                          "Bad address",
                          "Block device required",
                          "Resource busy",
                          "File exists",
                          "Cross-device link",
                          "Operation not supported by device",
                          "Not a directory",
                          "Is a directory",
                          "Invalid argument",
                          "Too many open files in system",
                          "Too many open files",
                          "Inappropriate ioctl for device",
                          "Text file busy",
                          "File too large",
                          "No space left on device",
                          "Illegal seek",
                          "Read-only file system",
                          "Too many links",
                          "Broken pipe",
                          "Numerical argument out of domain",
                          "Result too large",
                          "Resource temporarily unavailable",
                          "Operation now in progress",
                          "Operation already in progress",
                          "Socket operation on non-socket",
                          "Destination address required",
                          "Message too long",
                          "Protocol wrong type for socket",
                          "Protocol not available",
                          "Protocol not supported",
                          "Socket type not supported",
                          "Operation not supported",
                          "Protocol family not supported",
                          "Address family not supported by protocol family",
                          "Address already in use",
                          "Can't assign requested address",
                          "Network is down",
                          "Network is unreachable",
                          "Network dropped connection on reset",
                          "Software caused connection abort",
                          "Connection reset by peer",
                          "No buffer space available",
                          "Socket is already connected",
                          "Socket is not connected",
                          "Can't send after socket shutdown",
                          "Too many references: can't splice",
                          "Operation timed out",
                          "Connection refused",
                          "Too many levels of symbolic links",
                          "File name too long",
                          "Host is down",
                          "No route to host",
                          "Directory not empty",
                          "Too many processes",
                          "Too many users",
                          "Disc quota exceeded",
                          "Stale NFS file handle",
                          "Too many levels of remote in path",
                          "RPC struct is bad",
                          "RPC version wrong",
                          "RPC prog. not avail",
                          "Program version wrong",
                          "Bad procedure for program",
                          "No locks available",
                          "Function not implemented",
                          "Inappropriate file type or format",
                          "Authentication error",
                          "Need authenticator",
                          "Device power is off",
                          "Device error",
                          "Value too large to be stored in data type",
                          "Bad executable (or shared library)",
                          "Bad CPU type in executable",
                          "Shared library version mismatch",
                          "Malformed Mach-o file",
                          "Operation canceled",
                          "Identifier removed",
                          "No message of desired type",
                          "Illegal byte sequence",
                          "Attribute not found",
                          "Bad message",
                          "EMULTIHOP (Reserved)",
                          "No message available on STREAM",
                          "ENOLINK (Reserved)",
                          "No STREAM resources",
                          "Not a STREAM",
                          "Protocol error",
                          "STREAM ioctl timeout",
                          "Operation not supported on socket",
                          "Policy not found",
                          "State not recoverable",
                          "Previous owner died",
                          "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

static const char *maserror[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

void s21_int_to_string(char *str, int n) {
  int x = (n >= 0 ? n : -n);
  int it = 0;
  while (x != 0) {
    x /= 10;
    it++;
  }
  x = (n >= 0 ? n : -n);
  str[it] = '\0';
  while (it--) {
    str[it] = (char)('0' + x % 10);
    x /= 10;
  }
}

char *s21_strerror(int errnum) {
  char *res = S21_NULL;
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
    static char mes1[40] = ERROR;
    static char mes2[40];
    s21_int_to_string(mes2, errnum);
    s21_strncat(mes1, mes2, s21_strlen(mes2));
    res = mes1;
  } else
    res = (char *)maserror[errnum];
  return res;
}

void *s21_to_lower(const char *str) {
  char *str_copy = S21_NULL;
  if (str != S21_NULL) {
    int fl = 1;
    s21_size_t len = s21_strlen(str);
    str_copy = malloc((len + 1) * sizeof(char));
    if (str_copy == NULL) fl = 0;
    if (fl) {
      for (s21_size_t i = 0; i < len; i++) {
        int num = 0;
        num = str[i];
        if ((num >= 65 && num <= 90)) num += 32;
        str_copy[i] = num;
      }
      str_copy[len] = '\0';
    }
  }
  return str_copy;
}

void *s21_to_upper(const char *str) {
  char *str_copy = S21_NULL;
  if (str != S21_NULL) {
    int fl = 1;
    s21_size_t len = s21_strlen(str);
    str_copy = malloc((len + 1) * sizeof(char));
    if (str_copy == NULL) fl = 0;
    if (fl) {
      for (s21_size_t i = 0; i < len; i++) {
        int num = 0;
        num = str[i];
        if ((num >= 97 && num <= 122)) num -= 32;
        str_copy[i] = num;
      }
      str_copy[len] = '\0';
    }
  }
  return str_copy;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *answer = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t len_str = s21_strlen(str);
    s21_size_t len_src = s21_strlen(src);
    if (start_index <= len_src) {
      s21_size_t len_answer = len_str + len_src;
      answer = (char *)malloc(len_answer + 1);
      if (answer != S21_NULL) {
        s21_strncpy(answer, src, start_index);
        s21_strncpy(answer + start_index, str, len_str);
        s21_strncpy(answer + start_index + len_str, src + start_index,
                    len_src - start_index);
        answer[len_answer] = '\0';
      }
    }
  }
  return answer;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *answer = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    if (s21_strlen(src) > 0 && s21_strlen(trim_chars) > 0) {
      s21_size_t start = 0, end = s21_strlen(src) - 1, len = s21_strlen(src);
      while (start < len && s21_strchr(trim_chars, src[start])) start++;
      while (s21_strchr(trim_chars, src[end]) && end >= start) end--;
      if (start > end) {
        answer = (char *)malloc(1);
        if (answer != S21_NULL) answer[0] = '\0';
      } else {
        answer = (char *)malloc(end - start + 2);
        if (answer != S21_NULL) {
          s21_strncpy(answer, src + start, end - start + 1);
          answer[end - start + 1] = '\0';
        }
      }
    }
  }
  return answer;
}
int s21_sprintf(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int pos_format = 0;
  int pos_buffer = 0;
  char c;
  while ((c = format[pos_format]) != '\0') {
    if (c != '%') {
      buffer[pos_buffer++] = c;
      pos_format++;
    } else {
      pos_format++;
      parser_value(buffer, format, &pos_format, &pos_buffer, &args);
    }
  }
  va_end(args);
  buffer[pos_buffer] = '\0';
  return pos_buffer;
}

char *parser_value(char *buffer, const char *format, int *pos_format,
                   int *pos_buffer, va_list *args) {
  struct flags flag = {0, 0, 0, 0, 0};
  int width = 0;
  int precision = -1;
  char c = format[*pos_format];
  while (c == '0' || c == '+' || c == '-' || c == '#' || c == ' ') {
    parser_flags(c, &flag);
    (*pos_format)++;
    c = format[*pos_format];
  }

  if (format[*pos_format] >= '0' && format[*pos_format] <= '9')
    width = convert_str_in_int(format, pos_format);
  else if (format[*pos_format] == '*')
    width = va_arg(*args, int);

  if (format[*pos_format] == '.') {
    *pos_format += 1;
    if (format[*pos_format] >= '0' && format[*pos_format] <= '9')
      precision = convert_str_in_int(format, pos_format);
    else if (format[*pos_format] == '*')
      precision = va_arg(*args, int);
  }

  if (format[*pos_format] == 'c') {
    s21_sprintf_c(buffer, pos_buffer, width, &flag, args);
  } else if (format[*pos_format] == 'd') {
    s21_sprintf_d(buffer, pos_buffer, width, &flag, args);
  } else if (format[*pos_format] == 'f') {
    if (precision == -1) precision = 6;
    s21_sprintf_f(buffer, pos_buffer, width, &flag, precision, args);
  } else if (format[*pos_format] == 's') {
    s21_sprintf_s(buffer, pos_buffer, width, &flag, precision, args);
  } else if (format[*pos_format] == 'u') {
    s21_sprintf_u(buffer, pos_buffer, width, &flag, precision, args);
  } else {
    printf("Error?");
  }
  *pos_format += 1;
  return buffer;
}

void parser_flags(char c, struct flags *flag) {
  if (c == '0') {
    flag->zero = 1;
  } else if (c == '+') {
    flag->plus = 1;
    flag->space = 0;
  } else if (c == '-') {
    flag->minus = 1;
  } else if (c == '#') {
    flag->lat = 1;
  } else if (c == ' ') {
    flag->space = 1;
  }
  if (flag->plus) {
    flag->space = 0;
  }
}

int convert_str_in_int(const char *format, int *pos_format) {
  int width = 0;
  char c;
  while ((c = format[*pos_format]) >= '0' && c <= '9') {
    width *= 10;
    width += (int)(c - '0');
    *pos_format += 1;
  }
  return width;
}

char *convert_size_t_in_str(size_t number) {
  size_t len = 1;
  size_t temp = number;

  while (temp >= 10) {
    temp /= 10;
    len++;
  }

  char *str = malloc(len + 1);
  if (str) {
    str[len] = '\0';
    for (size_t i = len - 1; i < len; i--) {
      str[i] = '0' + (number % 10);
      number /= 10;
    }
  }

  return str;
}

int s21_sprintf_c(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, va_list *args) {
  int c = (char)va_arg(*args, int);
  int indent = (width > 1) ? (width - 1) : 0;
  if (flag->minus) {
    buffer[(*pos_buffer)++] = c;
    for (int i = 0; i < indent; i++) buffer[(*pos_buffer)++] = ' ';
  } else {
    for (int i = 0; i < indent; i++) buffer[(*pos_buffer)++] = ' ';
    buffer[(*pos_buffer)++] = c;
  }
  return 0;
}

int s21_sprintf_s(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, int precision, va_list *args) {
  const char *str = va_arg(*args, char *);
  if (!str) str = "(null)";

  int str_len = (int)s21_strlen(str);
  if (precision == -1 || precision > str_len) precision = str_len;
  int indent = (width > precision) ? (width - precision) : 0;

  if (flag->minus) {
    for (int i = 0; i < precision; i++) buffer[(*pos_buffer)++] = str[i];
    for (int i = 0; i < indent; i++) buffer[(*pos_buffer)++] = ' ';
  } else {
    for (int i = 0; i < indent; i++) buffer[(*pos_buffer)++] = ' ';
    for (int i = 0; i < precision; i++) buffer[(*pos_buffer)++] = str[i];
  }
  return 0;
}

int s21_sprintf_d(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, va_list *args) {
  int number = va_arg(*args, int);
  char sign;
  sign = (number >= 0 ? '+' : '-');
  char str_num[20];
  s21_int_to_string(str_num, number);
  if (flag->minus) {
    if (flag->plus || number < 0)
      buffer[(*pos_buffer)++] = sign;
    else
      width++;
    width--;

    for (s21_size_t i = 0; i < s21_strlen(str_num); i++) {
      buffer[(*pos_buffer)++] = str_num[i];
      width--;
    }
    for (int i = 0; width >= 0 && i < width; i++) {
      buffer[(*pos_buffer)++] = ' ';
    }
  } else if (flag->zero) {
    if (flag->plus || number < 0)
      buffer[(*pos_buffer)++] = sign;
    else
      width++;
    width--;
    for (s21_size_t i = 0; width >= 0 && i < width - s21_strlen(str_num); i++)
      buffer[(*pos_buffer)++] = '0';
    for (s21_size_t i = 0; i < s21_strlen(str_num); i++)
      buffer[(*pos_buffer)++] = str_num[i];
  } else {
    if (flag->plus || number < 0) width--;
    if (width > (int)s21_strlen(str_num))
      for (s21_size_t i = 0; width >= 0 && i < width - s21_strlen(str_num); i++)
        buffer[(*pos_buffer)++] = ' ';
    if (flag->plus || number < 0) buffer[(*pos_buffer)++] = sign;
    for (s21_size_t i = 0; i < s21_strlen(str_num); i++)
      buffer[(*pos_buffer)++] = str_num[i];
  }
  return 0;
}

int s21_sprintf_f(char *buffer, int *pos_buffer, int width, struct flags *flag,
                  int precision, va_list *args) {
  double number = va_arg(*args, double);
  if (number < 0) {
    flag->plus = 2;
    number *= -1;
  }
  int rank = 1;
  int copy_number = number;
  double copy_double = number - copy_number + 0.0000001;
  while (copy_number > 9) {
    rank++;
    copy_number /= 10;
  }
  int length_number = rank + (precision > 0) + precision;
  int length_zero = (width - length_number - (flag->plus > 0));
  length_zero *= (length_zero > 0) * (flag->minus == 0) * (flag->zero == 1);
  int length_void = (width - length_number - (flag->plus > 0));
  length_void *= (length_void > 0) * (flag->zero == 0 || flag->minus == 1);
  if (flag->space == 1 && (length_void == 0 || flag->minus == 1)) {
    buffer[(*pos_buffer)++] = ' ';
    length_void--;
    length_zero--;
  }
  for (int i = 0; i < length_zero; i++) {
    buffer[(*pos_buffer)++] = '0';
  }
  for (int i = 0; i < length_void && flag->minus == 0; i++) {
    buffer[(*pos_buffer)++] = ' ';
  }
  if (flag->plus > 0) buffer[(*pos_buffer)++] = (flag->plus == 1) ? '+' : '-';
  copy_number = number;
  for (int i = rank - 1; i >= 0; i--) {
    buffer[*pos_buffer + i] = '0' + copy_number % 10;
    copy_number /= 10;
  }
  *pos_buffer += rank;
  if (precision > 0) buffer[(*pos_buffer)++] = '.';
  for (int i = 0; i < precision; i++) {
    copy_double *= 10;
    copy_number = copy_double;
    buffer[(*pos_buffer)++] = '0' + copy_number % 10;
    copy_double -= copy_number;
  }
  for (int i = 0; i < length_void && flag->minus == 1; i++) {
    buffer[(*pos_buffer)++] = ' ';
  }
  return 0;
}

int s21_sprintf_u(char *buffer, int *pos_buffer, int width,
                  const struct flags *flag, int precision, va_list *args) {
  s21_size_t number = va_arg(*args, s21_size_t);
  char *str_insert = convert_size_t_in_str(number);
  s21_size_t len_str = s21_strlen(str_insert);
  int fl = 0;
  if (str_insert) {
    if (width > (int)len_str && width > precision) {
      for (s21_size_t i = 0; i < width - len_str && flag->minus == 0; i++) {
        buffer[(*pos_buffer)] = ' ';
        (*pos_buffer)++;
      }
    }

    if (precision > (int)len_str && precision > width) {
      for (s21_size_t i = 0; i < precision - len_str && flag->minus == 0; i++) {
        buffer[(*pos_buffer)] = '0';
        (*pos_buffer)++;
      }
    }

    for (s21_size_t i = 0; i < len_str; i++) {
      buffer[(*pos_buffer)] = str_insert[i];
      (*pos_buffer)++;
    }

    if (width > (int)len_str) {
      if (flag->minus) {
        for (s21_size_t i = 0; i < width - len_str; i++) {
          buffer[(*pos_buffer)] = ' ';
          (*pos_buffer)++;
        }
      }
    }

  } else
    fl = 1;
  if (str_insert) free(str_insert);
  return fl;
}
