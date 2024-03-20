#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  char *str1_ptr = (char *)str1;
  char *str2_ptr = (char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    res = str1_ptr[i] - str2_ptr[i];
    if (str1_ptr[i] != str2_ptr[i]) {
      break;
    }
  }
  return res;
}
