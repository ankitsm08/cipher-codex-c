#ifndef CIPHERS_SCYTALE_H
#define CIPHERS_SCYTALE_H

#include "cipher.h"

char *scytale_encrypt(const char *input, const cipher_params_t *params);
char *scytale_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_SCYTALE_H
