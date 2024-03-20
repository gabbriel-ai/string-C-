#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ptr = s21_NULL;
  char *str_ptr = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (str_ptr[i] == c) {
      ptr = &str_ptr[i];
      break;
    }
  }

  return ptr;
}
