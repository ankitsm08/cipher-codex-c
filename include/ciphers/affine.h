#ifndef AFFINE_H
#define AFFINE_H

#include "cipher.h"

char *affine_encrypt(const char *input, const cipher_params_t *params);
char *affine_decrypt(const char *input, const cipher_params_t *params);

#endif // !AFFINE_H
