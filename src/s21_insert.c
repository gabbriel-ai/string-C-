#include "s21_string.h"
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  if (str == s21_NULL && src != s21_NULL) {
    res = malloc(sizeof(char) * (s21_strlen(src) + 1));
    s21_strcpy(res, src);
  } else if (src != s21_NULL && str != s21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    s21_size_t new_len = src_len + str_len;

    res = malloc(sizeof(char) * (new_len + 1));

    if (res != s21_NULL) {
      for (s21_size_t i = 0, j = 0, m = 0; i < new_len; i++) {
        if (i < start_index || !str[m])
          res[i] = src[j++];
        else
          res[i] = str[m++];
      }
      res[new_len] = '\0';
    }
  }
  return res;
}