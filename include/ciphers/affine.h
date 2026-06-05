#ifndef CIPHERS_AFFINE_H
#define CIPHERS_AFFINE_H

#include "cipher.h"

char *affine_encrypt(const char *input, const cipher_params_t *params);
char *affine_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_AFFINE_H
