#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *mem = s21_NULL;

  if (str) mem = str;

  if (mem) {
    str = mem + s21_strspn(mem, delim);
    mem = str + s21_strcspn(str, delim);
    if (*mem != '\0') {
      *mem = '\0';
      ++mem;
    }
  }
  return *str != '\0' ? str : s21_NULL;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t flag = 0;
  s21_size_t count = 0;
  for (s21_size_t i = 0; str1[i]; i++) {
    flag = count;
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        count++;
        break;
      }
    }
    if (count == flag) break;
  }
  return count;
}