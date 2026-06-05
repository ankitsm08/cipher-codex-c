#include "ciphers/vigenere.h"
#include "cipher.h"
#include "utils/alpha.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int shift(char input_ch, char key_ch) {
  int key_base = alpha_index(key_ch);

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (input_ch - 'a' + key_base) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (input_ch - 'A' + key_base) % 26;

  return input_ch;
}

static int unshift(char input_ch, char key_ch) {
  int key_base = alpha_index(key_ch);

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (input_ch - 'a' - key_base + 26) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (input_ch - 'A' - key_base + 26) % 26;

  return input_ch;
}

char *vigenere_encrypt(const char *input, const cipher_params_t *params) {
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
    while (alpha_index(keyword[j]) == NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    char shifted = shift(input[i], keyword[j]);

    if (alpha_index(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = shifted;
  }

  output[len] = '\0';

  return output;
}

char *vigenere_decrypt(const char *input, const cipher_params_t *params) {
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
    while (alpha_index(keyword[j]) == NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    char unshifted = unshift(input[i], keyword[j]);

    if (alpha_index(input[i]) != NOT_ALPHABETIC)
      j = (j + 1) % keylen;

    output[i++] = unshifted;
  }

  output[len] = '\0';

  return output;
}
