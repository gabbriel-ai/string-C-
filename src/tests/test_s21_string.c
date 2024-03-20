#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_sprintf.h"
#include "../s21_string.h"

START_TEST(test_s21_strlen_basic) {
  const char *str = "Hello, world!";
  size_t expected_len = strlen(str);
  size_t result = s21_strlen(str);
  ck_assert_int_eq(result, expected_len);
}
END_TEST

START_TEST(test_s21_strlen_empty_string) {
  const char *str = "";
  size_t expected_len = strlen(str);
  size_t result = s21_strlen(str);
  ck_assert_int_eq(result, expected_len);
}
END_TEST

START_TEST(test_s21_strlen_null_character) {
  const char *str = "Hello\0World";
  size_t expected_len = strlen(str);
  size_t result = s21_strlen(str);
  ck_assert_int_eq(result, expected_len);
}
END_TEST

START_TEST(test_s21_strpbrk_basic) {
  const char *str = "Hello, world!";
  const char *search = "wl";
  char *expected_result = s21_strpbrk(str, search);
  char *result = strpbrk(str, search);
  ck_assert_str_eq(result, expected_result);
}
END_TEST

START_TEST(test_s21_strpbrk_empty_string) {
  const char *str = "";
  const char *search = "";
  char *expected_result = s21_strpbrk(str, search);
  char *result = strpbrk(str, search);
  ck_assert_ptr_null(expected_result);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_strpbrk_empty_search) {
  const char *str = "Hello, world!";
  const char *search = "";
  char *expected_result = s21_strpbrk(str, search);
  char *result = strpbrk(str, search);
  ck_assert_ptr_null(expected_result);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_strerror_basic) {
#ifdef __APPLE__
  for (int err = 0; err < MAC_ERR_MESSAGES_COUNT; err++) {
    char *result = s21_strerror(err);
    char *expected_result = strerror(err);
    ck_assert_str_eq(result, expected_result);
  }
#endif

#ifdef __linux__
  for (int err = 0; err < LINUX_ERR_MESSAGES_COUNT; err++) {
    char *result = s21_strerror(err);
    char *expected_result = strerror(err);
    ck_assert_str_eq(result, expected_result);
  }
#endif
}
END_TEST

START_TEST(test_s21_strerror_unknown_error) {
  for (int err = 200; err < 400; err++) {
    char *result = s21_strerror(err);
    char *expected_result = strerror(err);
    ck_assert_str_eq(result, expected_result);
  }
}

START_TEST(s21_strcspn_1) {
  char s1[] = "H e l l o\0";
  char s2[] = "lo\0";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(s21_strcspn_2) {
  char s1[] = "Hello\0";
  char s2[] = "HE\0";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(s21_strcspn_3) {
  char s1[] = "Hello\0";
  char s2[] = "\0";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(s21_strcspn_4) {
  char s1[] = "Hello\0";
  char s2[] = "Hello\0";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(s21_strcspn_5) {
  char s1[] = "Hello\0";
  char s2[] = "hELLO\0";
  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(s21_strcspn_6) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(s21_strcspn_7) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(s21_strcspn_8) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(s21_strcspn_9) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(s21_strcspn_10) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(s21_strcspn_11) {
  char *str = "hello, world";
  char *keys = "wl";
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_12) {
  char *str = "";
  char *keys = "wl";
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_13) {
  char *str = "hello, world";
  char *keys = "";
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_14) {
  char *str = "";
  char *keys = "";
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_15) {
  char test1[] = "DawnBreaker";
  char test2[] = "Dawn";
  char test3[] = "Primal Beast";
  char test4[] = "beast";
  char test5[] = "0/";
  char test6[] = "//#";
  char test7[] = " ";
  char test8[] = "0987654321";
  char test9[] = "0";
  char test10[] = "1";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_uint_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_uint_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_uint_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_uint_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
  ck_assert_uint_eq(s21_strcspn(test8, test9), strcspn(test8, test9));
  ck_assert_uint_eq(s21_strcspn(test8, test10), strcspn(test8, test10));
}
END_TEST

START_TEST(s21_strncmp_1) {
  char s1[50] = "Hello world\0";
  char s3[50] = "Hello worl\0";
  ck_assert_int_eq(s21_strncmp(s1, s3, 3), strncmp(s1, s3, 3));
}
END_TEST

START_TEST(s21_strncmp_2) {
  char s1[50] = "Hello world\0";
  char s3[50] = "Hello\0";
  ck_assert_int_eq(s21_strncmp(s1, s3, 4), strncmp(s1, s3, 4));
}
END_TEST

START_TEST(s21_strncmp_3) {
  char s1[50] = "\n\0";
  char s3[50] = "\n\0";
  ck_assert_int_eq(s21_strncmp(s1, s3, 1), strncmp(s1, s3, 1));
}
END_TEST

START_TEST(s21_strncmp_4) {
  char s1[50] = "privet\0";
  char s3[50] = "privet medved\0";
  ck_assert_int_eq(s21_strncmp(s1, s3, 2), strncmp(s1, s3, 2));
}
END_TEST

START_TEST(s21_strncmp_5) {
  char s1[] = "";
  char s2[] = "";
  s21_size_t n_byte = 0;

  int got = s21_strncmp(s1, s2, n_byte);
  int expected = strncmp(s1, s2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strncmp_8) {
  char s1[] = "floppa";
  char s2[] = "floppa";
  s21_size_t n_byte = 6;

  int got = s21_strncmp(s1, s2, n_byte);
  int expected = strncmp(s1, s2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strncmp_9) {
  char s1[] = "floppabazbazkotya";
  char s2[] = "floppabaz";
  s21_size_t n_byte = 10;

  int got = s21_strncmp(s1, s2, n_byte);
  int expected = strncmp(s1, s2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strncmp_10) {
  char s1[] = "floppa";
  char s2[] = "floppa";
  s21_size_t n_byte = 1;

  int got = s21_strncmp(s1, s2, n_byte);
  int expected = strncmp(s1, s2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strncmp_11) {
  char *test_str = "12345";
  char *test_substr = "12345";
  s21_size_t n = 3;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_12) {
  char *test_str = "12345";
  char *test_substr = "12345";
  s21_size_t n = 5;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_13) {
  char *test_str = "12345";
  char *test_substr = "22345";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_14) {
  char *test_str = "22345";
  char *test_substr = "";
  s21_size_t n = 3;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_16) {
  char *test_str = "12345";
  char *test_substr = "13545";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_17) {
  char *test_str = "";
  char *test_substr = "";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_18) {
  char *test_str = "22345";
  char *test_substr = "12345";
  s21_size_t n = 7;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncpy_1) {
  char s1[] = "Hello world\0";
  char s2[] = "Hello \0";
  char s3[] = "Hello world\0";
  char s4[] = "Hello \0";
  s21_strncpy(s1, s2, 3);
  strncpy(s3, s4, 3);
  ck_assert_str_eq(s1, s3);
}
END_TEST

START_TEST(s21_strncpy_2) {
  char s1[] = "Hello\0";
  char s2[] = "123\0";
  char s3[] = "Hello\0";
  char s4[] = "123\0";
  s21_strncpy(s1, s2, 2);
  strncpy(s3, s4, 2);
  ck_assert_str_eq(s1, s3);
}
END_TEST

START_TEST(s21_strncpy_3) {
  char s1[] = " \n\0";
  char s2[] = " \0";
  char s3[] = " \n\0";
  char s4[] = " \0";
  s21_strncpy(s1, s2, 1);
  strncpy(s3, s4, 1);
  ck_assert_str_eq(s1, s3);
}
END_TEST

START_TEST(s21_strncpy_4) {
  char s1[] = "\0";
  char s2[] = "\0";
  char s3[] = "\0";
  char s4[] = "\0";
  s21_strncpy(s1, s2, 1);
  strncpy(s3, s4, 1);
  ck_assert_str_eq(s1, s3);
}
END_TEST

START_TEST(s21_strncpy_5) {
  char s1[] = "H e l l o\0";
  char s2[] = "H E L L O\0";
  char s3[] = "H e l l o\0";
  char s4[] = "H E L L O\0";
  s21_strncpy(s1, s2, 5);
  strncpy(s3, s4, 5);
  ck_assert_str_eq(s1, s3);
}
END_TEST

START_TEST(s21_strncpy_6) {
  char src[] = "123";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(s21_strncpy_7) {
  char src[] = "";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(s21_strncpy_8) {
  char src[] = "123";
  char res[5] = "123";
  char exp[5] = "123";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(s21_strncpy_9) {
  char src[] = "123";
  char res[7] = "123";
  char exp[7] = "123";
  s21_size_t n_byte = 2;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(s21_strncpy_10) {
  char src[] = "Str1ng";
  char res[7 + 7] = "Str1ng";
  char exp[7 + 7] = "Str1ng";
  s21_size_t n_byte = 7;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(s21_strncpy_11) {
  char test_dest[100] = "Hello world gello world gellortwls";
  char test_dest2[100] = "Hello world gello world gellortwls";
  const char test_src[100] = "taktaktak";
  s21_size_t n = 5;
  char *s21_res = s21_strncpy(test_dest, test_src, n);
  ck_assert_str_eq(s21_res, strncpy(test_dest2, test_src, n));
}
END_TEST

START_TEST(s21_strncpy_12) {
  char test_dest[50] = "hello world again! and again";
  char test_dest2[50] = "hello world again! and again";
  const char test_src[100] = "taktaktak";
  s21_size_t n = 10;
  char *s21_res = s21_strncpy(test_dest, test_src, n);
  ck_assert_str_eq(s21_res, strncpy(test_dest2, test_src, n));
}
END_TEST

START_TEST(test_s21_memchr_found_k) {
  const char *str = "I like pink";
  char find = 'k';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_not_found_f) {
  const char *str = "I like pink";
  char find = 'f';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_found_1) {
  const char *str = "I 1ike pink";
  char find = '1';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_not_found_1) {
  const char *str = "I like pink";
  char find = '1';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_found_space) {
  const char *str = "I like pink";
  char find = ' ';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_found_in_empty_str) {
  const char *str = " ";
  char find = '&';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memchr_null_pointer) {
  const char *str = NULL;
  char find = '&';
  ck_assert_pstr_eq(s21_memchr(str, find, 0), memchr(str, find, 0));
}
END_TEST

START_TEST(test_s21_memchr_end_str) {
  const char *str = "\0";
  char find = '&';
  ck_assert_pstr_eq(s21_memchr(str, find, strlen(str) + 1),
                    memchr(str, find, strlen(str) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_more) {
  const char *str1 = "I like pink";
  const char *str2 = "I like green";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_equal) {
  const char *str1 = "I like pink";
  const char *str2 = "I like pink";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_less) {
  const char *str1 = "I like green";
  const char *str2 = "I like pink";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_empty_strs) {
  const char *str1 = " ";
  const char *str2 = " ";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_one_empty_str) {
  const char *str1 = "I like pink";
  const char *str2 = " ";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcmp_null_pointer) {
  const char *str1 = NULL;
  const char *str2 = "I like pink";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

START_TEST(test_s21_memcmp_end_str) {
  const char *str1 = "\0";
  const char *str2 = "I like pink";
  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1) + 1),
                   memcmp(str1, str2, strlen(str1) + 1));
}
END_TEST

START_TEST(test_s21_memcpy_all) {
  const char *str = "I like pink";
  char dest1[25];
  char dest2[25];
  s21_memcpy(dest1, str, strlen(str) + 1);
  memcpy(dest2, str, strlen(str) + 1);
  ck_assert_mem_eq(dest1, dest2, strlen(str) + 1);
}
END_TEST

START_TEST(test_s21_memcpy_5) {
  const char *str = "I like pink";
  char dest1[25];
  char dest2[25];
  s21_memcpy(dest1, str, 5);
  memcpy(dest2, str, 5);
  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_s21_memcpy_symbols) {
  const char *str = "12345&&&***";
  char dest1[25];
  char dest2[25];
  s21_memcpy(dest1, str, strlen(str) + 1);
  memcpy(dest2, str, strlen(str) + 1);
  ck_assert_mem_eq(dest1, dest2, strlen(str) + 1);
}
END_TEST

START_TEST(aboba_test) {
  char res[] = "aboba";
  char expected[] = "aboba";
  char replace = 'g';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(empty) {
  char res[] = " ";
  char expected[] = " ";
  char replace = '\0';
  s21_size_t n_byte = 0;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(zero_byte_memset) {
  char res[] = "esketit";
  char expected[] = "esketit";
  char replace = 'y';
  s21_size_t n_byte = 0;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(replace_on_register_sim) {
  char res[] = "esketit";
  char expected[] = "esketit";
  char replace = 'S';
  s21_size_t n_byte = 3;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(replace_on_register_num) {
  char res[] = "esk1etiT";
  char expected[] = "esk1etiT";
  char replace = '1';
  s21_size_t n_byte = 5;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(long_string) {
  char res[] =
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA";
  char expected[] =
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA";
  char replace = '1';
  s21_size_t n_byte = 5;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(abobasnutsa_find_a) {
  char src[] = "abobasnutsa";
  char find = 'a';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(abobasnutAsa_find_A) {
  char src[] = "abobasnuAtsa";
  char find = 'A';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(abobasnutA1sa_find_1) {
  char src[] = "abobasnuA1sa";
  char find = '1';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(abobasnutAsa_find_Z) {
  char src[] = "abobasnuA1sa";
  char find = 'Z';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(abobasnutAsa_find_3) {
  char src[] = "abobasnuA1sa";
  char find = '3';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(empty_src_strchr) {
  char src[] = " ";
  char find = '3';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(all_empty) {
  char src[] = " ";
  char res[] = " ";
  char expected[] = " ";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_byte_strncat) {
  char src[] = "abosal";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(empty_src_strncat) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(cd_abosa) {
  char src[] = "abosal";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(string) {
  char src[] = "abosal";
  char res[25] = "koleka";
  char expected[25] = "koleka";
  s21_size_t n_byte = 6;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(BIGFLOPPA) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(BIGFLOPPA2) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(BIGFLOPPA3) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(BIGFLOPPA4) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 10;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_char) {
  char src[] = "\0";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(test_s21_strstr_basic) {
  const char haystack[] = "Hello World";
  const char needle[] = "World";
  char *result_s21 = s21_strstr(haystack, needle);
  char *result_strstr = strstr(haystack, needle);
  ck_assert_ptr_eq(result_s21, result_strstr);
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  char haystack[] = "hello world";
  char needle[] = "universe";
  char *expected = strstr(haystack, needle);
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strstr_empty_string) {
  char empty[] = "";
  char needle[] = "world";
  char *expected = strstr(empty, needle);
  char *result = s21_strstr(empty, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_basic) {
  char str[] = "hello world";
  char *expected = strrchr(str, 'l');
  char *result = s21_strrchr(str, 'l');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  char str[] = "hello world";
  char *expected = strrchr(str, 'z');
  char *result = s21_strrchr(str, 'z');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
  char empty[] = "";
  char *expected = strrchr(empty, 'a');
  char *result = s21_strrchr(empty, 'a');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_last_char) {
  char str[] = "hello";
  char *expected = strrchr(str, 'o');
  char *result = s21_strrchr(str, 'o');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_first_char) {
  char str[] = "hello";
  char *expected = strrchr(str, 'h');
  char *result = s21_strrchr(str, 'h');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_null_terminator) {
  char str[] = "hello\0world";
  char *expected = strrchr(str, '\0');
  char *result = s21_strrchr(str, '\0');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_multiple_occurrences) {
  char str[] = "hello world";
  char *expected = strrchr(str, 'o');
  char *result = s21_strrchr(str, 'o');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strrchr_case_sensitive) {
  char str[] = "Hello World";
  char *expected = strrchr(str, 'H');
  char *result = s21_strrchr(str, 'H');
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strtok_basic) {
  char str[] = "This,is;a,test,string";
  char input[sizeof(str)];
  strcpy(input, str);
  const char delim[] = ",;";
  char *token_s21 = s21_strtok(input, delim);
  char *token_strtok = strtok(str, delim);
  ck_assert_str_eq(token_s21, token_strtok);
}
END_TEST

START_TEST(test_s21_strtok_empty_string) {
  char empty[] = "";
  char delim[] = " ,!?";
  char *expected = NULL;

  char empty_copy[sizeof(empty)];
  strcpy(empty_copy, empty);
  char *token_strtok = strtok(empty_copy, delim);

  char *token_s21_strtok = s21_strtok(empty, delim);

  ck_assert_ptr_eq(token_s21_strtok, expected);
  ck_assert_ptr_eq(token_strtok, expected);
}
END_TEST

START_TEST(test_s21_strtok_no_delimiters) {
  char str[] = "HelloWorldHowAreYou";
  char delim[] = "";
  char *expected_tokens[] = {"HelloWorldHowAreYou"};
  char *expected = NULL;
  char *result;

  char str_copy[sizeof(str)];
  strcpy(str_copy, str);
  char *token_strtok = strtok(str_copy, delim);

  char *token_s21_strtok = s21_strtok(str, delim);

  result = token_s21_strtok;
  ck_assert_str_eq(result, expected_tokens[0]);
  ck_assert_str_eq(token_s21_strtok, token_strtok);

  token_s21_strtok = s21_strtok(NULL, delim);
  token_strtok = strtok(NULL, delim);
  ck_assert_ptr_eq(token_s21_strtok, expected);
  ck_assert_ptr_eq(token_strtok, expected);
}
END_TEST

START_TEST(test_s21_trim) {
  char str[] = "HelloWorldHowAreYou";
  char expected[] = "elloWorldHowAreYo";
  char *result = s21_trim(str, "Hu");
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty) {
  char str[] = "   HelloWorldHowAreYou   ";
  char expected[] = "HelloWorldHowAreYou";
  char *result = s21_trim(str, " ");
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(str_empty) {
  char str[] = "";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_empty) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "";
  char expected[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_and_str_eq) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_test1) {
  char str[] = "+!!++Abo+ba++00";
  char trim_ch[] = "+!0-";
  char expected[] = "Abo+ba";
  char *got = (char *)s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_test2) {
  char str[] = "Ab000cd0";
  char trim_ch[] = "003";
  char expected[] = "Ab000cd";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_test3) {
  char str[] = "DoNotTouch";
  char trim_ch[] = "Not";
  char expected[] = "DoNotTouch";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_test4) {
  char str[] = "&* !!sc21 * **";
  char trim_ch[] = "&!* ";
  char expected[] = "sc21";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(trim_test5) {
  char str[] = " Good morning!    ";
  char trim_ch[] = " ";
  char expected[] = "Good morning!";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(empty_spaces) {
  char str[] = "        abc         ";
  char trim_ch[] = "";
  char expected[] = "abc";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(null_ptr_trim_chars) {
  char str[] = "        abc         ";
  char *trim_ch = NULL;
  char expected[] = "abc";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str[] = "HELLOwORLD";
  char expected[] = "helloworld";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  char str[] = "";
  char expected[] = "";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str[] = "heLLOWORLD";
  char expected[] = "HELLOWORLD";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  char str[] = "";
  char expected[] = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert) {
  char str[] = "bacdef";
  char expected[] = "bactestdef";
  char *result = s21_insert(str, "test", 3);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty) {
  char str[] = "";
  char expected[] = "test";
  char *result = s21_insert(str, "test", 0);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(insert_test1) {
  char str[] = "Shlepa";
  char src[] = "I love my . He is very kind!";
  s21_size_t index = 10;
  char expected[] = "I love my Shlepa. He is very kind!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(insert_test2) {
  char str[] = "Hello, ";
  char src[] = "Aboba!";
  s21_size_t index = 0;
  char expected[] = "Hello, Aboba!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(insert_test3) {
  char str[] = "";
  char src[] = "";
  s21_size_t index = 100;
  char *expected = "";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(insert_test4) {
  char *src = NULL;
  char *str = NULL;
  s21_size_t index = 100;
  char *expected = NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(insert_test5) {
  char str[] = "Monkey";
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space Monkey ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(insert_str_null) {
  char *str = NULL;
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space  ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
  char c1[100] = "a";
  char c2[100] = "a";
  char c3[100] = "lolkek";
  char c4[100] = "lolkek";
  ck_assert_int_eq(sprintf(c1, "test %d%d%d", 5, 6, 10),
                   s21_sprintf(c2, "test %d%d%d", 5, 6, 10));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c3 + 6, "%d", -6000),
                   s21_sprintf(c4 + 6, "%d", -6000));
  ck_assert_str_eq(c3, c4);
  ck_assert_int_eq(sprintf(c1, "%10d %-10d %4.10d", 1, 666, 2544325),
                   s21_sprintf(c2, "%10d %-10d %4.10d", 1, 666, 2544325));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%+4.10d", 1), s21_sprintf(c2, "%+4.10d", 1));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%+20.10d", 1), s21_sprintf(c2, "%+20.10d", 1));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%-20.10d", 1), s21_sprintf(c2, "%-20.10d", 1));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%+-20.10d", 1),
                   s21_sprintf(c2, "%+-20.10d", 1));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%-+10d", 666), s21_sprintf(c2, "%-+10d", 666));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%% % d", 1), s21_sprintf(c2, "%% % d", 1));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%10d", -2147483647),
                   s21_sprintf(c2, "%10d", -2147483647));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%10ld", -21474836488),
                   s21_sprintf(c2, "%10ld", -21474836488));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%10hd", 55643),
                   s21_sprintf(c2, "%10hd", 55643));
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%u%15u%20u", 4321u, -34567, 2342u);
  int r2 = s21_sprintf(str2, "%u%15u%20u", 4321u, -34567, 2342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_sprintf_c) {
  char c1[100] = "a";
  char c2[100] = "a";
  ck_assert_int_eq(sprintf(c1, "test %c%c%lc", 'a', 'c', 'c'),
                   s21_sprintf(c2, "test %c%c%c", 'a', 'c', 'c'));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c1, "%lc", L'a'), s21_sprintf(c2, "%lc", L'a'));
  ck_assert_str_eq(c1, c2);

  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%c%c%c%c%c%c%c%c%c%c", 'a', 'e', 'f', 'R', 'Q', 10,
                   'P', 'L', 20, 'x');
  int r2 = s21_sprintf(str2, "%c%c%c%c%c%c%c%c%c%c", 'a', 'e', 'f', 'R', 'Q',
                       10, 'P', 'L', 20, 'x');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  char str1[1000];
  char str2[1000];
  char s[10] = {'h', 'e', 'l', 'l', 'o'};
  int r1 = sprintf(str1, "%s%10s%s%7.2s%10.3s %5.3s%5s%s%s%6.33s", "aboba",
                   "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", "QWERTY",
                   "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
  int r2 = s21_sprintf(str2, "%s%10s%s%7.2s%10.3s %5.3s%5s%s%s%6.33s", "aboba",
                       "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", "QWERTY",
                       "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

// START_TEST(test_s21_sprintf_o) {
//   char str1[1000];
//   char str2[1000];
//   int r1 = sprintf(str1, "%#o", 12345);
//   int r2 = s21_sprintf(str2, "%#o", 12345);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_x) {
//   char str1[1000];
//   char str2[1000];
//   int r1 = sprintf(str1, "%#x", 12345);
//   int r2 = s21_sprintf(str2, "%#x", 12345);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_X) {
//   char str1[1000];
//   char str2[1000];
//   int r1 = sprintf(str1, "%#X", 12345);
//   int r2 = s21_sprintf(str2, "%#X", 12345);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_n) {
//   char str1[1000];
//   char str2[1000];
//   int val = 0;
//   int r1 = sprintf(str1, "hello%nworld", &val);
//   int r2 = s21_sprintf(str2, "hello%nworld", &val);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
//   // Now check if `val` got the correct value.
//   ck_assert_int_eq(val, strlen("hello"));
// }
// END_TEST

START_TEST(test_s21_sprintf_i) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%i", -12345);
  int r2 = s21_sprintf(str2, "%i", -12345);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

// START_TEST(test_s21_sprintf_p) {
//   char str1[1000];
//   char str2[1000];
//   int val = 123;
//   int r1 = sprintf(str1, "%p", (void *)&val);
//   int r2 = s21_sprintf(str2, "%p", (void *)&val);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_flag_0) {
//   char str1[1000];
//   char str2[1000];
//   int r1 = sprintf(str1, "%05d", 123);
//   int r2 = s21_sprintf(str2, "%05d", 123);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_zero_number) {
//   char str1[100];
//   char str2[100];
//   int r1 = sprintf(str1, "%05d", 0);
//   int r2 = s21_sprintf(str2, "%05d", 0);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   char str3[100];
//   char str4[100];
//   int r3 = sprintf(str3, "%05d", 0);
//   int r4 = s21_sprintf(str4, "%05d", 0);
//   ck_assert_str_eq(str3, str4);
//   ck_assert_int_eq(r3, r4);
// }
// END_TEST

// START_TEST(test_s21_sprintf_upper_case_conversion) {
//   char str1[100];
//   char str2[100];
//   int num1 = 10; // ASCII code for 'A'
//   int num2 = 13; // ASCII code for 'D'
//   int num3 = 14; // ASCII code for 'E'

//   // Test case for '%x' format with upper case conversion
//   int r1 = sprintf(str1, "%x", num1);
//   int r2 = s21_sprintf(str2, "%x", num1);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   r1 = sprintf(str1, "%x", num2);
//   r2 = s21_sprintf(str2, "%x", num2);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   r1 = sprintf(str1, "%x", num3);
//   r2 = s21_sprintf(str2, "%x", num3);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   // Test case for '%X' format with upper case conversion
//   r1 = sprintf(str1, "%X", num1);
//   r2 = s21_sprintf(str2, "%X", num1);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   r1 = sprintf(str1, "%X", num2);
//   r2 = s21_sprintf(str2, "%X", num2);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);

//   r1 = sprintf(str1, "%X", num3);
//   r2 = s21_sprintf(str2, "%X", num3);
//   ck_assert_str_eq(str1, str2);
//   ck_assert_int_eq(r1, r2);
// }
END_TEST

START_TEST(test_s21_sprintf_print_c) {
  char str1[100];
  char str2[100];
  char ch = 'A';

  // Test case with positive width and without minus flag
  int r1 = sprintf(str1, "%5c", ch);
  int r2 = s21_sprintf(str2, "%5c", ch);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);

  // Test case with negative width and minus flag
  r1 = sprintf(str1, "%8c", ch);
  r2 = s21_sprintf(str2, "%8c", ch);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  char c1[100] = "a";
  char c2[100] = "a";
  char c3[100] = "lolkek";
  char c4[100] = "lolkek";
  ck_assert_int_eq(sprintf(c1, "test %f %f %f", 5.1, 0.1, -0.00001),
                   s21_sprintf(c2, "test %f %f %f", 5.1, 0.1, -0.00001));
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(sprintf(c3 + 6, "%f", -6000.00006),
                   s21_sprintf(c4 + 6, "%f", -6000.00006));
  ck_assert_str_eq(c3, c4);
  ck_assert_int_eq(sprintf(c3, "%flolkek%f", -6000.00006, -1.0),
                   s21_sprintf(c4, "%flolkek%f", -6000.00006, -1.0));
  ck_assert_str_eq(c3, c4);
  ck_assert_int_eq(sprintf(c3, "%.0f", 99.99), s21_sprintf(c4, "%.0f", 99.99));
  printf("%s\n", c4);
  ck_assert_str_eq(c3, c4);

  // imported
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char *s1 = "Hello";
  const char *s2 = "Hell";
  const size_t n = 4;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_strncmp_equal_strings) {
  const char *s1 = "Hello";
  const char *s2 = "Hello";
  const size_t n = 5;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_strncmp_different_strings) {
  const char *s1 = "Hello";
  const char *s2 = "World";
  const size_t n = 3;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_strncmp_n_greater_than_length_s1) {
  const char *s1 = "Hello";
  const char *s2 = "Hello";
  const size_t n = 10;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_strncmp_n_greater_than_length_s2) {
  const char *s1 = "Hello";
  const char *s2 = "Hi";
  const size_t n = 10;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_strncmp_n_zero) {
  const char *s1 = "Hello";
  const char *s2 = "Hi";
  const size_t n = 0;
  int result_s21 = s21_strncmp(s1, s2, n);
  int result_standard = strncmp(s1, s2, n);
  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

Suite *s21_test_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_tests");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen_basic);
  tcase_add_test(tc_core, test_s21_strlen_empty_string);
  tcase_add_test(tc_core, test_s21_strlen_null_character);

  tcase_add_test(tc_core, test_s21_strpbrk_basic);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_string);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_search);

  tcase_add_test(tc_core, test_s21_strerror_basic);
  tcase_add_test(tc_core, test_s21_strerror_unknown_error);

  tcase_add_test(tc_core, s21_strcspn_1);
  tcase_add_test(tc_core, s21_strcspn_2);
  tcase_add_test(tc_core, s21_strcspn_3);
  tcase_add_test(tc_core, s21_strcspn_4);
  tcase_add_test(tc_core, s21_strcspn_5);
  tcase_add_test(tc_core, s21_strcspn_6);
  tcase_add_test(tc_core, s21_strcspn_7);
  tcase_add_test(tc_core, s21_strcspn_8);
  tcase_add_test(tc_core, s21_strcspn_9);
  tcase_add_test(tc_core, s21_strcspn_10);
  tcase_add_test(tc_core, s21_strcspn_11);
  tcase_add_test(tc_core, s21_strcspn_12);
  tcase_add_test(tc_core, s21_strcspn_13);
  tcase_add_test(tc_core, s21_strcspn_14);
  tcase_add_test(tc_core, s21_strcspn_15);

  tcase_add_test(tc_core, s21_strncmp_1);
  tcase_add_test(tc_core, s21_strncmp_2);
  tcase_add_test(tc_core, s21_strncmp_3);
  tcase_add_test(tc_core, s21_strncmp_4);
  tcase_add_test(tc_core, s21_strncmp_5);
  tcase_add_test(tc_core, s21_strncmp_8);
  tcase_add_test(tc_core, s21_strncmp_9);
  tcase_add_test(tc_core, s21_strncmp_10);
  tcase_add_test(tc_core, s21_strncmp_11);
  tcase_add_test(tc_core, s21_strncmp_12);
  tcase_add_test(tc_core, s21_strncmp_13);
  tcase_add_test(tc_core, s21_strncmp_14);
  tcase_add_test(tc_core, s21_strncmp_16);
  tcase_add_test(tc_core, s21_strncmp_17);
  tcase_add_test(tc_core, s21_strncmp_18);

  tcase_add_test(tc_core, s21_strncpy_1);
  tcase_add_test(tc_core, s21_strncpy_2);
  tcase_add_test(tc_core, s21_strncpy_3);
  tcase_add_test(tc_core, s21_strncpy_4);
  tcase_add_test(tc_core, s21_strncpy_5);
  tcase_add_test(tc_core, s21_strncpy_6);
  tcase_add_test(tc_core, s21_strncpy_7);
  tcase_add_test(tc_core, s21_strncpy_8);
  tcase_add_test(tc_core, s21_strncpy_9);
  tcase_add_test(tc_core, s21_strncpy_10);
  tcase_add_test(tc_core, s21_strncpy_11);
  tcase_add_test(tc_core, s21_strncpy_12);

  tcase_add_test(tc_core, test_s21_memchr_found_k);
  tcase_add_test(tc_core, test_s21_memchr_not_found_f);
  tcase_add_test(tc_core, test_s21_memchr_found_1);
  tcase_add_test(tc_core, test_s21_memchr_not_found_1);
  tcase_add_test(tc_core, test_s21_memchr_found_space);
  tcase_add_test(tc_core, test_s21_memchr_found_in_empty_str);
  tcase_add_test(tc_core, test_s21_memchr_null_pointer);
  tcase_add_test(tc_core, test_s21_memchr_end_str);

  tcase_add_test(tc_core, test_s21_memcmp_more);
  tcase_add_test(tc_core, test_s21_memcmp_equal);
  tcase_add_test(tc_core, test_s21_memcmp_less);
  tcase_add_test(tc_core, test_s21_memcmp_empty_strs);
  tcase_add_test(tc_core, test_s21_memcmp_one_empty_str);
  tcase_add_test(tc_core, test_s21_memcmp_null_pointer);
  tcase_add_test(tc_core, test_s21_memcmp_end_str);

  tcase_add_test(tc_core, test_s21_memcpy_all);
  tcase_add_test(tc_core, test_s21_memcpy_5);
  tcase_add_test(tc_core, test_s21_memcpy_symbols);

  tcase_add_test(tc_core, aboba_test);
  tcase_add_test(tc_core, empty);
  tcase_add_test(tc_core, zero_byte_memset);
  tcase_add_test(tc_core, replace_on_register_sim);
  tcase_add_test(tc_core, replace_on_register_num);
  tcase_add_test(tc_core, long_string);

  tcase_add_test(tc_core, abobasnutsa_find_a);
  tcase_add_test(tc_core, abobasnutAsa_find_A);
  tcase_add_test(tc_core, abobasnutA1sa_find_1);
  tcase_add_test(tc_core, abobasnutAsa_find_Z);
  tcase_add_test(tc_core, abobasnutAsa_find_3);
  tcase_add_test(tc_core, empty_src_strchr);

  tcase_add_test(tc_core, all_empty);
  tcase_add_test(tc_core, zero_byte_strncat);
  tcase_add_test(tc_core, empty_src_strncat);
  tcase_add_test(tc_core, cd_abosa);
  tcase_add_test(tc_core, string);
  tcase_add_test(tc_core, BIGFLOPPA);
  tcase_add_test(tc_core, BIGFLOPPA2);
  tcase_add_test(tc_core, BIGFLOPPA3);
  tcase_add_test(tc_core, BIGFLOPPA4);
  tcase_add_test(tc_core, zero_char);

  tcase_add_test(tc_core, test_s21_strstr_basic);
  tcase_add_test(tc_core, test_s21_strstr_not_found);
  tcase_add_test(tc_core, test_s21_strstr_empty_string);

  tcase_add_test(tc_core, test_s21_strrchr_basic);
  tcase_add_test(tc_core, test_s21_strrchr_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_empty_string);

  tcase_add_test(tc_core, test_s21_strrchr_last_char);
  tcase_add_test(tc_core, test_s21_strrchr_first_char);
  tcase_add_test(tc_core, test_s21_strrchr_null_terminator);
  tcase_add_test(tc_core, test_s21_strrchr_multiple_occurrences);
  tcase_add_test(tc_core, test_s21_strrchr_case_sensitive);

  tcase_add_test(tc_core, test_s21_strtok_basic);
  tcase_add_test(tc_core, test_s21_strtok_empty_string);
  tcase_add_test(tc_core, test_s21_strtok_no_delimiters);

  tcase_add_test(tc_core, test_s21_trim);
  tcase_add_test(tc_core, test_s21_trim_empty);
  tcase_add_test(tc_core, all_empty);
  tcase_add_test(tc_core, str_empty);
  tcase_add_test(tc_core, trim_empty);
  tcase_add_test(tc_core, trim_and_str_eq);

  tcase_add_test(tc_core, trim_test1);
  tcase_add_test(tc_core, trim_test2);
  tcase_add_test(tc_core, trim_test3);
  tcase_add_test(tc_core, trim_test4);
  tcase_add_test(tc_core, trim_test5);
  tcase_add_test(tc_core, empty_spaces);
  tcase_add_test(tc_core, null_ptr_trim_chars);

  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_to_lower_empty);

  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_upper_empty);

  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_insert_empty);

  tcase_add_test(tc_core, insert_test1);
  tcase_add_test(tc_core, insert_test2);
  tcase_add_test(tc_core, insert_test3);
  tcase_add_test(tc_core, insert_test4);
  tcase_add_test(tc_core, insert_test5);
  tcase_add_test(tc_core, insert_str_null);

  tcase_add_test(tc_core, test_s21_sprintf_d);
  tcase_add_test(tc_core, test_s21_sprintf_u);
  tcase_add_test(tc_core, test_s21_sprintf_c);
  tcase_add_test(tc_core, test_s21_sprintf_s);
  tcase_add_test(tc_core, test_s21_sprintf_percent);
  // tcase_add_test(tc_core, test_s21_sprintf_o);
  // tcase_add_test(tc_core, test_s21_sprintf_x);
  // tcase_add_test(tc_core, test_s21_sprintf_X);
  // tcase_add_test(tc_core, test_s21_sprintf_n);
  tcase_add_test(tc_core, test_s21_sprintf_i);
  // tcase_add_test(tc_core, test_s21_sprintf_p);
  // tcase_add_test(tc_core, test_s21_sprintf_flag_0);
  // tcase_add_test(tc_core, test_s21_sprintf_zero_number);
  // tcase_add_test(tc_core, test_s21_sprintf_upper_case_conversion);
  tcase_add_test(tc_core, test_s21_sprintf_print_c);
  tcase_add_test(tc_core, test_s21_sprintf_f);

  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncmp_equal_strings);
  tcase_add_test(tc_core, test_s21_strncmp_different_strings);
  tcase_add_test(tc_core, test_s21_strncmp_n_greater_than_length_s1);
  tcase_add_test(tc_core, test_s21_strncmp_n_greater_than_length_s2);
  tcase_add_test(tc_core, test_s21_strncmp_n_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_test_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
