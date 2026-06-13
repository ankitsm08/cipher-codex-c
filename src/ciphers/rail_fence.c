#include "ciphers/rail_fence.h"
#include "cipher.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *rail_fence_encrypt(const char *input, const cipher_params_t *params) {
  const int key = params->number.value;

  const size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  if (key <= 1 || len <= 2) {
    strcpy(output, input);
    return output;
  }

  size_t idx = 0;
  for (int i = 0; i < key; i++) {
    bool movingDown = true;
    for (size_t j = i; j < len; movingDown = !movingDown) {
      output[idx++] = input[j];
      // distance of current cell to top or bottom
      // depending on moving direction
      int dist = (movingDown ? 2 * (key - i - 1) : 2 * i) - 1;
      // dist < 0 for top and bottom row
      j += ((dist > 0) ? dist : (2 * key - 4 - dist)) + 1;
    }
  }

  output[len] = '\0';
  return output;
}

char *rail_fence_decrypt(const char *input, const cipher_params_t *params) {
  const int key = params->number.value;

  const size_t len = strlen(input);

  char *output = malloc(len + 1);
  if (!output)
    return NULL;

  if (key <= 1 || len <= 2) {
    strcpy(output, input);
    return output;
  }

  size_t idx = 0;
  for (int i = 0; i < key; i++) {
    bool movingDown = true;
    for (size_t j = i; j < len; movingDown = !movingDown) {
      output[j] = input[idx++];
      int dist = (movingDown ? 2 * (key - i - 1) : 2 * i) - 1;
      j += ((dist > 0) ? dist : (2 * key - 4 - dist)) + 1;
    }
  }

  output[len] = '\0';
  return output;
}
