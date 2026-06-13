#include "ciphers/gronsfeld.h"
#include "cipher.h"
#include "utils/alpha.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int shift(char input_ch, char key_ch) {
  int key_num = digit_value(key_ch);

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (input_ch - 'a' + key_num) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (input_ch - 'A' + key_num) % 26;

  return input_ch;
}

static int unshift(char input_ch, char key_ch) {
  int key_num = digit_value(key_ch);

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (input_ch - 'a' - key_num + 26) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (input_ch - 'A' - key_num + 26) % 26;

  return input_ch;
}

char *gronsfeld_encrypt(const char *input, const cipher_params_t *params) {
  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  char *keyword = params->string.text;
  size_t keylen = strlen(keyword);
  if (keylen == 0) {
    free(output);
    return NULL;
  }

  if (!has_num(keyword, keylen)) {
    free(output);
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < len) {
    while (digit_value(keyword[j]) == NOT_NUMERIC)
      j = (j + 1) % keylen;

    char shifted = shift(input[i], keyword[j]);

    if (alpha_index(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = shifted;
  }

  output[len] = '\0';

  return output;
}

char *gronsfeld_decrypt(const char *input, const cipher_params_t *params) {
  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  char *keyword = params->string.text;
  size_t keylen = strlen(keyword);
  if (keylen == 0) {
    free(output);
    return NULL;
  }

  if (!has_num(keyword, keylen)) {
    free(output);
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < len) {
    while (digit_value(keyword[j]) == NOT_NUMERIC)
      j = (j + 1) % keylen;

    char unshifted = unshift(input[i], keyword[j]);

    if (alpha_index(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = unshifted;
  }

  output[len] = '\0';

  return output;
}
