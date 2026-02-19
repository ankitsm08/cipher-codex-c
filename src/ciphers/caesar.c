#include "ciphers/caesar.h"
#include "cipher.h"
#include <stdlib.h>
#include <string.h>

static char shift_char(const char ch, int shift) {
  if ('a' <= ch && ch <= 'z') {
    return 'a' + (ch - 'a' + shift) % 26;
  }
  if ('A' <= ch && ch <= 'Z') {
    return 'A' + (ch - 'A' + shift) % 26;
  }
  return ch;
}

char *caesar_encrypt(const char *input, const cipher_params_t *params) {
  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  int shift = params->number;
  shift = ((shift % 26) + 26) % 26;

  for (size_t i = 0; i < len; i++) {
    output[i] = shift_char(input[i], shift);
  }

  output[len] = '\0';
  return output;
}

char *caesar_decrypt(const char *input, const cipher_params_t *params) {
  cipher_params_t decrypt_params = *params;
  decrypt_params.number = -decrypt_params.number;
  return caesar_encrypt(input, &decrypt_params);
}
