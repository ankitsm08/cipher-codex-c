#ifndef BEAUFORT_H
#define BEAUFORT_H

#include "cipher.h"

char *beaufort_encrypt(const char *input, const cipher_params_t *params);
char *beaufort_decrypt(const char *input, const cipher_params_t *params);

#endif // !BEAUFORT_H
