#include "cipher.h"

static cipher_t cipher_registry[] = {
};

size_t cipher_count(void) {
  return sizeof(cipher_registry) / sizeof(cipher_registry[0]);
}

const cipher_t *get_cipher(size_t index) {
  if (index >= cipher_count())
    return NULL;
  return &cipher_registry[index];
}
