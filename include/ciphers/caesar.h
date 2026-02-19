#ifndef CAESAR_H
#define CAESAR_H

#include "cipher.h"
char *caesar_encrypt(const char *, const cipher_params_t *params);
char *caesar_decrypt(const char *, const cipher_params_t *params);

#endif // !CAESAR_H
