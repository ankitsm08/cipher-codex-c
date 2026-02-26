#include "ciphers/scytale.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *scytale_encrypt(const char *input, const cipher_params_t *params) {
  if (params->number <= 0)
    return NULL;

  size_t len = strlen(input);

  const size_t width = (size_t)params->number;
  const size_t height = (len + width - 1) / width;

  char *output = malloc(width * height + 1);
  if (!output)
    return NULL;

  for (size_t i = 0; i < width * height; i++) {
    int r = i / height;
    int c = i % height;
    size_t idx = c * width + r;

    if (idx >= len)
      output[i] = '~';
    else
      output[i] = input[idx];
  }

  output[width * height] = '\0';
  return output;
}

char *scytale_decrypt(const char *input, const cipher_params_t *params) {
  if (params->number <= 0)
    return NULL;

  size_t len = strlen(input);

  const size_t width = (size_t)params->number;
  const size_t height = (len + width - 1) / width;

  char *output = malloc(width * height + 1);
  if (!output)
    return NULL;

  for (size_t i = 0; i < width * height; i++) {
    int r = i / width;
    int c = i % width;
    size_t idx = c * height + r;

    if (idx < len)
      output[i] = input[idx];
  }

  for (size_t i = width * height; i > 0; i--) {
    if (output[i - 1] != '~') {
      output[i] = '\0';
      break;
    }
  }

  return output;
}
