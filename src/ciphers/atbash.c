#include "ciphers/atbash.h"
#include "cipher.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static char mirror_char(char ch) {
  if ('a' <= ch && ch <= 'z')
    return 'z' - (ch - 'a');
  if ('A' <= ch && ch <= 'Z')
    return 'Z' - (ch - 'A');
  return ch;
}

char *atbash_encrypt(const char *input, const cipher_params_t *params) {
  (void)params; // ignore params

  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  for (size_t i = 0; i < len; i++) {
    output[i] = mirror_char(input[i]);
  }

  output[len] = '\0';
  return output;
}

char *atbash_decrypt(const char *input, const cipher_params_t *params) {
  return atbash_encrypt(input, params);
}
