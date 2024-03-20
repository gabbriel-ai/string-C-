#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *current_symbol = s21_NULL;
  while (*str) {
    if (*str == c) {
      current_symbol = str;
    }
    str++;
  }
  return (char *)(c == '\0' ? str : current_symbol);
}