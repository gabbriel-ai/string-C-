#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *start = dest;
  s21_size_t i = 0;
  for (; i < n && *src != '\0'; i++, src++, dest++) {
    *dest = *src;
  }
  for (; i < n; i++, dest++) {
    *dest = '\0';
  }
  return start;
}
