#include "s21_string.h"

char *s21_strerror(int errnum) {
#ifdef __APPLE__
  if (errnum == 0) {
    return "Undefined error: 0";
  }
  static const char *mac_err_messages[MAC_ERR_MESSAGES_COUNT] = {
      MAC_ERR_MESSAGES};
  if (errnum > 0 && errnum < MAC_ERR_MESSAGES_COUNT) {
    return (char *)mac_err_messages[errnum];
  }

  const char *prefix = "Unknown error: ";
#endif

#ifdef __linux__
  if (errnum == 0) {
    return "Success";
  }
  static const char *linux_err_messages[LINUX_ERR_MESSAGES_COUNT] = {
      LINUX_ERR_MESSAGES};
  if (errnum > 0 && errnum < LINUX_ERR_MESSAGES_COUNT) {
    return (char *)linux_err_messages[errnum];
  }

  const char *prefix = "Unknown error ";
#endif

  static char unknown_error_message[50];
  s21_size_t index = 0;

  while (*prefix && index < sizeof(unknown_error_message) - 1) {
    unknown_error_message[index++] = *prefix++;
  }

  int temp = errnum;
  int digits = 0;
  while (temp != 0) {
    temp /= 10;
    digits++;
  }

  char number_str[10];
  number_str[digits] = '\0';

  for (int i = digits - 1; i >= 0; i--) {
    number_str[i] = '0' + (errnum % 10);
    errnum /= 10;
  }

  int i = 0;
  while (*number_str && index < sizeof(unknown_error_message) - 1) {
    unknown_error_message[index++] = number_str[i++];
  }

  unknown_error_message[index] = '\0';

  return unknown_error_message;
}
