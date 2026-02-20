#ifndef ATBASH_H
#define ATBASH_H

#include "cipher.h"

char *atbash_encrypt(const char *input, const cipher_params_t *params);
char *atbash_decrypt(const char *input, const cipher_params_t *params);

#endif // !ATBASH_H
