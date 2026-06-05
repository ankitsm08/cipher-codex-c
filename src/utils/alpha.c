#include "utils/alpha.h"
#include <stdbool.h>

int alpha_index(char ch) {
  if ('a' <= ch && ch <= 'z')
    return ch - 'a';
  if ('A' <= ch && ch <= 'Z')
    return ch - 'A';
  return NOT_ALPHABETIC;
}

int digit_value(char ch) {
  if ('0' <= ch && ch <= '9')
    return ch - '0';
  return NOT_NUMERIC;
}

bool has_alpha(const char *str, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (alpha_index(str[i]) != NOT_ALPHABETIC)
      return true;
  }
  return false;
}

bool has_num(const char *str, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (digit_value(str[i]) != NOT_NUMERIC)
      return true;
  }
  return false;
}
