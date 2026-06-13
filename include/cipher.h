#ifndef CIPHER_H
#define CIPHER_H

#include <stddef.h>

typedef enum cipher_params_type {
  PARAM_NONE,
  PARAM_NUMBER,
  PARAM_2_NUMBERS,
  PARAM_STRING,
  PARAM_2_STRINGS,
} cipher_params_type_t;

typedef struct number {
  int value;
} number_t;

typedef struct two_numbers {
  int value1;
  int value2;
} two_number_t;

typedef struct string {
  char *text;
  size_t length;
} string_t;

typedef struct two_string {
  char *text1;
  char *text2;
  size_t length1;
  size_t length2;
} two_string_t;

typedef union cipher_params {
  number_t number;
  two_number_t two_numbers;
  string_t string;
  two_string_t two_strings;
} cipher_params_t;

typedef struct cipher {
  const char *name;
  cipher_params_type_t param_type;
  char *(*encrypt)(const char *input, const cipher_params_t *params);
  char *(*decrypt)(const char *input, const cipher_params_t *params);
} cipher_t;

size_t cipher_count(void);
const cipher_t *get_cipher(size_t index);

#endif // CIPHER_H
