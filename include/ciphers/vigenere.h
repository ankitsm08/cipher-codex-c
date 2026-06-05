#ifndef CIPHERS_VIGENERE_H
#define CIPHERS_VIGENERE_H

#include "cipher.h"

char *vigenere_encrypt(const char *input, const cipher_params_t *params);
char *vigenere_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_VIGENERE_H
