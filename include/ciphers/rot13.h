#ifndef ROT13_H
#define ROT13_H

#include "cipher.h"

char *rot13_encrypt(const char *, const cipher_params_t *params);
char *rot13_decrypt(const char *, const cipher_params_t *params);

#endif // !ROT13_H
