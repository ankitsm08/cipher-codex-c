#ifndef CIPHERS_RAIL_FENCE_H
#define CIPHERS_RAIL_FENCE_H

#include "cipher.h"

char *rail_fence_encrypt(const char *input, const cipher_params_t *params);
char *rail_fence_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_RAIL_FENCE_H
