#ifndef VIGINERE_H
#define VIGINERE_H

#include "cipher.h"

char *vigenere_encrypt(const char *input, const cipher_params_t *params);
char *vigenere_decrypt(const char *input, const cipher_params_t *params);

#endif // !VIGINERE_H
