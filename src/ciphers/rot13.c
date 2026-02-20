#include "ciphers/rot13.h"
#include "cipher.h"
#include "ciphers/caesar.h"

char *rot13_encrypt(const char *input, const cipher_params_t *params) {
  cipher_params_t rot13_encrypt_params = *params;
  rot13_encrypt_params.number = 13;
  return caesar_encrypt(input, &rot13_encrypt_params);
}

char *rot13_decrypt(const char *input, const cipher_params_t *params) {
  cipher_params_t rot13_decrypt_params = *params;
  rot13_decrypt_params.number = -13;
  return caesar_encrypt(input, &rot13_decrypt_params);
}
