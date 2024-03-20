#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *str_res = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    str_res = (char *)malloc(sizeof(char) * (len + 1));
    if (str_res != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          str_res[i] = str[i] - 'A' + 'a';
        } else {
          str_res[i] = str[i];
        }
      }
      str_res[len] = '\0';
    }
  }
  return str_res;
}
