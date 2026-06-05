#ifndef CIPHERS_BEAUFORT_H
#define CIPHERS_BEAUFORT_H

#include "cipher.h"

char *beaufort_encrypt(const char *input, const cipher_params_t *params);
char *beaufort_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_BEAUFORT_H
