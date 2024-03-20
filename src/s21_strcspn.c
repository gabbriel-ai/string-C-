#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  for (; *str1 != '\0'; str1++) {
    if (s21_strchr(str2, *str1) != s21_NULL) {
      break;
    }
    count++;
  }
  return count;
}
