#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct {
  int minus;          // -
  int plus;           // +
  int space;          // пробел
  int hash;           // #
  int zero;           // 0
  int width;          // ширина
  int dot;            // наличие точки
  int number_system;  // разряд системы
  int accuracy;       // точность
  char length;        // %lf Lf Ld etc
  int flag_to_size;   // наличие '+' '-' ' '
  int upper_case;     // регистр
  int e;
  int g;
} Flag;

const char *set_flags(Flag *flags, const char *format, va_list *arguments);
const char *get_flags(const char *format, Flag *flags);
const char *get_width(const char *format, int *width, va_list *arguments);
char *parser(char *str, char *src, const char *format, Flag flags,
             va_list *arguments);
char *print_decimal(char *str, Flag flags, va_list *arguments);
s21_size_t get_size_for_buffer(Flag *flags, long int num);
int dec_to_str(Flag flags, long int num, char *str, s21_size_t size);
char num_to_char(int num, int upper_case);
Flag set_number_system(Flag flags, char format);
char *print_u(char *str, Flag flags, char format, va_list *arguments);
s21_size_t get_buf_size_unsigned_decimal(Flag flags, unsigned long int num);
int unsigned_dec_to_str(char *buffer, Flag flags, unsigned long int num,
                        s21_size_t size_to_num);
char *print_c(char *str, Flag flags, int symb);
char *print_s(char *str, Flag flags, va_list *arguments);
char *print_p(char *str, Flag *flags, va_list *arguments);

#endif  // S21_SPRINTF_H_