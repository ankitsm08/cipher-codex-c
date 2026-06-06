#include "ciphers/columnar_transposition.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static inline int ceil_height(size_t len, int keylen) {
  return (len + keylen - 1) / keylen;
}

static void keyword_order(const char *key, int len, int *order) {
  char last_char = CHAR_MIN;
  int out = 0;

  while (out < len) {
    char next_char = CHAR_MAX;

    for (int i = 0; i < len; i++) {
      if (next_char > key[i] && last_char < key[i])
        next_char = key[i];
    }

    last_char = next_char;

    for (int i = 0; i < len; i++) {
      if (key[i] == next_char)
        order[out++] = i;
    }
  }
}

char *columnar_transposition_encrypt(const char *input,
                                     const cipher_params_t *params) {
  char *keyword = params->string;
  int keylen = strlen(keyword);
  int order[keylen];

  keyword_order(keyword, keylen, order);

  size_t len = strlen(input);
  int height = ceil_height(len, keylen);
  char *output = malloc(keylen * height + 1);
  if (!output)
    return NULL;

  size_t idx = 0;
  for (int c = 0; c < keylen; c++) {
    int col = order[c];
    for (int r = 0; r < height; r++) {
      size_t pos = r * keylen + col;
      if (pos < len)
        output[idx++] = input[pos];
      else
        output[idx++] = '_';
    }
  }

  output[keylen * height] = '\0';
  return output;
}

char *columnar_transposition_decrypt(const char *input,
                                     const cipher_params_t *params) {
  char *keyword = params->string;
  int keylen = strlen(keyword);
  int order[keylen];

  keyword_order(keyword, keylen, order);

  size_t len = strlen(input);
  int height = ceil_height(len, keylen);
  char *output = malloc(keylen * height + 1);
  if (!output)
    return NULL;

  size_t idx = 0;
  for (int c = 0; c < keylen; c++) {
    int col = order[c];
    for (int r = 0; r < height; r++) {
      size_t pos = r * keylen + col;
      if (pos < len)
        output[pos] = input[idx++];
    }
  }

  output[keylen * height] = '\0';
  return output;
}
