#ifndef GRONSFELD_H
#define GRONSFELD_H

#include "cipher.h"

char *gronsfeld_encrypt(const char *input, const cipher_params_t *params);
char *gronsfeld_decrypt(const char *input, const cipher_params_t *params);

#endif // !GRONSFELD_H
