#ifndef POLYBIUS_SQAURE_H
#define POLYBIUS_SQAURE_H

#include "cipher.h"

char *polybius_square_encrypt(const char *input, const cipher_params_t *params);
char *polybius_square_decrypt(const char *input, const cipher_params_t *params);

#endif // !POLYBIUS_SQAURE_H
