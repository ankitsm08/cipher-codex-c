#include "cipher.h"
#include "ciphers/affine.h"
#include "ciphers/atbash.h"
#include "ciphers/caesar.h"
#include "ciphers/rot13.h"
#include "ciphers/scytale.h"

static cipher_t cipher_registry[] = {
    {"Caesar", PARAM_NUMBER, caesar_encrypt, caesar_decrypt},
    {"ROT13", PARAM_NONE, rot13_encrypt, rot13_decrypt},
    {"Atbash", PARAM_NONE, atbash_encrypt, atbash_decrypt},
    {"Affine", PARAM_2_NUMBERS, affine_encrypt, affine_decrypt},
    {"Scytale", PARAM_NUMBER, scytale_encrypt, scytale_decrypt},
};

size_t cipher_count(void) {
  return sizeof(cipher_registry) / sizeof(cipher_registry[0]);
}

const cipher_t *get_cipher(size_t index) {
  if (index >= cipher_count())
    return NULL;
  return &cipher_registry[index];
}
