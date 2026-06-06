#ifndef CIPHERS_COLUMNAR_TRANSPOSITION_H
#define CIPHERS_COLUMNAR_TRANSPOSITION_H

#include "cipher.h"

char *columnar_transposition_encrypt(const char *input,
                                     const cipher_params_t *params);
char *columnar_transposition_decrypt(const char *input,
                                     const cipher_params_t *params);

#endif // CIPHERS_COLUMNAR_TRANSPOSITION_H
