#include "ciphers/vigenere.h"
#include "cipher.h"
#include <stdlib.h>
#include <string.h>

static int base(char ch) {
  if ('a' <= ch && ch <= 'z')
    return ch - 'a';
  if ('A' <= ch && ch <= 'Z')
    return ch - 'A';
  return -1;
}

static int shift(char input_ch, char key_ch) {
  int key_base = base(key_ch);

  if (key_base == -1)
    return -1;

  if ('a' <= input_ch && input_ch <= 'z')
    return 'a' + (input_ch - 'a' + key_base) % 26;
  if ('A' <= input_ch && input_ch <= 'Z')
    return 'A' + (input_ch - 'A' + key_base) % 26;

  return input_ch;
}

static int unshift(char input_ch, char key_ch) {
  int key_base = base(key_ch);

  if (key_base == -1)
    return -1;

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
  if (keylen == 0)
    return NULL;

  size_t i = 0, j = 0;
  while (i < len) {
    while (base(keyword[j]) == -1)
      j = (j + 1) % keylen;

    char shifted = shift(input[i], keyword[j]);

    if (base(input[i]) != -1)
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
  if (keylen == 0)
    return NULL;

  size_t i = 0, j = 0;
  while (i < len) {
    while (base(keyword[j]) == -1)
      j = (j + 1) % keylen;

    char unshifted = unshift(input[i], keyword[j]);

    if (base(input[i]) != -1)
      j = (j + 1) % keylen;

    output[i++] = unshifted;
  }

  output[len] = '\0';

  return output;
}
