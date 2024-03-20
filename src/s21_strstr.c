#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *str_res = s21_NULL;
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  if (haystack_len >= needle_len) {
    for (s21_size_t i = 0; i <= haystack_len - needle_len; i++) {
      bool is_found = 1;
      for (s21_size_t j = i, k = 0; k < needle_len; j++, k++) {
        if (haystack[j] != needle[k]) {
          is_found = 0;
          break;
        }
      }
      if (is_found) {
        str_res = (char *)haystack + i;
        break;
      }
    }
  }

  return str_res;
}
