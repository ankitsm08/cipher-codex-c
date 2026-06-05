#ifndef CIPHERS_CAESAR_H
#define CIPHERS_CAESAR_H

#include "cipher.h"

char *caesar_encrypt(const char *input, const cipher_params_t *params);
char *caesar_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_CAESAR_H
