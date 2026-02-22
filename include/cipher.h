#ifndef CIPHER_H
#define CIPHER_H

#include <stddef.h>

typedef enum cipher_params_type {
  PARAM_NONE,
  PARAM_NUMBER,
  PARAM_2_NUMBERS,
  PARAM_STRING,
} cipher_params_type_t;

typedef struct cipher_params {
  int number;
  int number2;
  char *string;
} cipher_params_t;

typedef struct cipher {
  const char *name;
  cipher_params_type_t param_type;
  char *(*encrypt)(const char *input, const cipher_params_t *params);
  char *(*decrypt)(const char *input, const cipher_params_t *params);
} cipher_t;

size_t cipher_count(void);
const cipher_t *get_cipher(size_t index);

#endif // !CIPHER_H
