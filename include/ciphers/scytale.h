#ifndef SCYTALE_H
#define SCYTALE_H

#include "cipher.h"

char *scytale_encrypt(const char *, const cipher_params_t *params);
char *scytale_decrypt(const char *, const cipher_params_t *params);

#endif // !SCYTALE_H
