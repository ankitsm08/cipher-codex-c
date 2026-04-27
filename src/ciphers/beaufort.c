#include "ciphers/beaufort.h"
#include "cipher.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum { NOT_ALPHABETIC = -1 };

static int base(char ch) {
  if ('a' <= ch && ch <= 'z')
    return ch - 'a';
  if ('A' <= ch && ch <= 'Z')
    return ch - 'A';
  return NOT_ALPHABETIC;
}

static int shift(char input_ch, char key_ch) {
  int key_base = base(key_ch);

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (key_base - (input_ch - 'a') + 26) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (key_base - (input_ch - 'A') + 26) % 26;

  return input_ch;
}

inline static int unshift(char input_ch, char key_ch) {
  // Unshift is the same as shift
  return shift(input_ch, key_ch);
}

static bool has_alpha(const char *str, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (base(str[i]) != NOT_ALPHABETIC)
      return true;
  }
  return false;
}

char *beaufort_encrypt(const char *input, const cipher_params_t *params) {
  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  char *keyword = params->string;
  size_t keylen = strlen(keyword);
  if (keylen == 0) {
    free(output);
    return NULL;
  }

  if (!has_alpha(keyword, keylen)) {
    free(output);
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < len) {
    while (base(keyword[j]) == NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    char shifted = shift(input[i], keyword[j]);

    if (base(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = shifted;
  }

  output[len] = '\0';

  return output;
}

char *beaufort_decrypt(const char *input, const cipher_params_t *params) {
  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  char *keyword = params->string;
  size_t keylen = strlen(keyword);
  if (keylen == 0) {
    free(output);
    return NULL;
  }

  if (!has_alpha(keyword, keylen)) {
    free(output);
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < len) {
    while (base(keyword[j]) == NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    char unshifted = unshift(input[i], keyword[j]);

    if (base(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = unshifted;
  }

  output[len] = '\0';

  return output;
}
