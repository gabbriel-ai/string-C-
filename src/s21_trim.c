#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *str_res = s21_NULL;
  if (trim_chars == s21_NULL || trim_chars[0] == '\0') {
    str_res = s21_trim(src, "\t\n ");
  } else {
    if (src != s21_NULL) {
      // left trim
      s21_size_t left_index = 0;
      while (src[left_index] != '\0' &&
             (s21_is_trim(trim_chars, src[left_index]))) {
        left_index++;
      }
      // right trim
      s21_size_t right_index = s21_strlen(src) - 1;
      while (right_index != left_index - 1 &&
             (s21_is_trim(trim_chars, src[right_index]))) {
        right_index--;
      }
      // copy from left to right
      s21_size_t len = right_index - left_index + 1;
      str_res = (char *)malloc(sizeof(char) * (len + 1));
      for (s21_size_t i = 0; i < len; i++, left_index++) {
        str_res[i] = src[left_index];
      }
      str_res[len] = '\0';
    }
  }

  return str_res;
}

bool s21_is_trim(const char *trim_chars, const char symbol) {
  while (*trim_chars) {
    if (*trim_chars == symbol) {
      return true;
    }
    trim_chars++;
  }
  return false;
}
