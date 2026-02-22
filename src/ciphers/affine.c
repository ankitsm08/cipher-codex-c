#include "ciphers/affine.h"
#include "cipher.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Extended Euclidean Algorithm
static int extended_gcd(int a, int b, int *x, int *y) {
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }

  int x1, y1;
  int gcd = extended_gcd(b, a % b, &x1, &y1);

  *x = y1;
  *y = x1 - (a / b) * y1;

  return gcd;
}

static char transform(char ch, int a, int b) {
  if ('a' <= ch && ch <= 'z')
    return 'a' + ((a * (ch - 'a') + b) % 26 + 26) % 26;
  if ('A' <= ch && ch <= 'Z')
    return 'A' + ((a * (ch - 'A') + b) % 26 + 26) % 26;
  return ch;
}

static char inverse_transform(char ch, int inv_a, int b) {
  if ('a' <= ch && ch <= 'z')
    return 'a' + ((inv_a * ((ch - 'a') - b)) % 26 + 26) % 26;
  if ('A' <= ch && ch <= 'Z')
    return 'A' + ((inv_a * ((ch - 'A') - b)) % 26 + 26) % 26;
  return ch;
}

char *affine_encrypt(const char *input, const cipher_params_t *params) {
  int a = params->number;
  int b = params->number2;
  b = (b % 26 + 26) % 26;

  int x, y;
  int gcd = extended_gcd(a, 26, &x, &y);
  if (gcd != 1)
    return NULL;

  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  for (size_t i = 0; i < len; i++) {
    output[i] = transform(input[i], a, b);
  }

  output[len] = '\0';
  return output;
}

char *affine_decrypt(const char *input, const cipher_params_t *params) {
  int a = params->number;
  int b = params->number2;
  b = (b % 26 + 26) % 26;

  int x, y;
  int gcd = extended_gcd(a, 26, &x, &y);
  if (gcd != 1)
    return NULL;
  int inv_a = (x % 26 + 26) % 26;

  size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  for (size_t i = 0; i < len; i++) {
    output[i] = inverse_transform(input[i], inv_a, b);
  }

  output[len] = '\0';
  return output;
}
