#ifndef CIPHERS_POLYBIUS_SQUARE_H
#define CIPHERS_POLYBIUS_SQUARE_H

#include "cipher.h"

char *polybius_square_encrypt(const char *input, const cipher_params_t *params);
char *polybius_square_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_POLYBIUS_SQUARE_H
