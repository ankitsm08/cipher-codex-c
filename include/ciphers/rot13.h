#ifndef CIPHERS_ROT13_H
#define CIPHERS_ROT13_H

#include "cipher.h"

char *rot13_encrypt(const char *input, const cipher_params_t *params);
char *rot13_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_ROT13_H
