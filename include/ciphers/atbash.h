#ifndef CIPHERS_ATBASH_H
#define CIPHERS_ATBASH_H

#include "cipher.h"

char *atbash_encrypt(const char *input, const cipher_params_t *params);
char *atbash_decrypt(const char *input, const cipher_params_t *params);

#endif // CIPHERS_ATBASH_H
