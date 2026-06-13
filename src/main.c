#include "cipher.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operation { ENCRYPT, DECRYPT };

#define STARTING_MESSAGE_CAP 16
#define MAX_KEYWORD_LENGTH 128

int main(void) {
  int RETURN_CODE = 0;

  printf("Operations: \n1. Encrypt\n2. Decrypt\nChoose the operation: ");
  int operation;
  if (scanf("%d", &operation) != 1)
    return 1;
  operation--;
  if (operation != ENCRYPT && operation != DECRYPT) {
    printf("Invalid operation\n");
    return 1;
  }

  printf("Available Ciphers: \n");
  for (size_t i = 0; i < cipher_count(); i++) {
    const cipher_t *cipher = get_cipher(i);
    if (!cipher)
      continue;
    printf("[%zu] %s\n", i + 1, cipher->name);
  }

  int cipher_id;
  printf("Enter the cipher id: ");
  if (scanf("%d", &cipher_id) != 1)
    return 1;
  cipher_id--;

  const cipher_t *cipher = get_cipher(cipher_id);
  if (!cipher) {
    printf("Invalid cipher id\n");
    return 1;
  }

  int len = 0, cap = STARTING_MESSAGE_CAP;
  char c = 0, prev = 0;
  char *input = malloc(cap);

  printf("Enter your message: \n");

  while ((c = getchar()) != '\n' && c != EOF)
    ;

  while ((c = getchar()) != EOF) {
    if (c == '\n' && prev == '\n')
      break;
    prev = c;
    input[len++] = c;

    if (len >= cap) {
      cap *= 2;
      input = realloc(input, cap);
    }
  }

  if (len > 0 && input[len - 1] == '\n')
    input[len - 1] = '\0';
  else
    input[len] = '\0';

  cipher_params_t params;

  switch (cipher->param_type) {
  case PARAM_NONE:
    break;

  case PARAM_NUMBER: {
    printf("Enter the key: ");
    if (scanf("%d", &params.number.value) != 1) {
      free(input);
      return 1;
    }
    break;
  }

  case PARAM_2_NUMBERS: {
    printf("Enter the number 1: ");
    if (scanf("%d", &params.two_numbers.value1) != 1) {
      RETURN_CODE = -1;
      break;
    }
    printf("Enter the number 2: ");
    if (scanf("%d", &params.two_numbers.value2) != 1) {
      RETURN_CODE = -1;
      break;
    }
    break;
  }

  case PARAM_STRING: {
    char *keyword = malloc(MAX_KEYWORD_LENGTH + 1);
    params.string.text = keyword;

    printf("Enter the keyword: ");
    if (scanf("%128s", params.string.text) != 1) {
      RETURN_CODE = -1;
      break;
    }
    params.string.length = strlen(keyword);
    break;
  }

  case PARAM_2_STRINGS: {
    char *keyword1 = malloc(MAX_KEYWORD_LENGTH + 1);
    params.two_strings.text1 = keyword1;

    printf("Enter the first keyword: ");
    if (scanf("%128s", params.two_strings.text1) != 1) {
      RETURN_CODE = -1;
      break;
    }
    params.two_strings.length1 = strlen(keyword1);

    char *keyword2 = malloc(MAX_KEYWORD_LENGTH + 1);
    params.two_strings.text2 = keyword2;

    printf("Enter the second keyword: ");
    if (scanf("%128s", params.two_strings.text2) != 1) {
      RETURN_CODE = -1;
      break;
    }
    params.two_strings.length2 = strlen(keyword2);

    break;
  }
  }

  if (RETURN_CODE == 0) {
    char *result = NULL;
    if (operation == ENCRYPT) {
      result = cipher->encrypt(input, &params);
    } else {
      result = cipher->decrypt(input, &params);
    }
    if (result) {
      printf("Result:\n%s\n", result);
    } else {
      printf("Operation failed\n");
      RETURN_CODE = -1;
    }
    free(result);
  }

  free(input);

  switch (cipher->param_type) {
  case PARAM_STRING:
    free(params.string.text);
    break;
  case PARAM_2_STRINGS:
    free(params.two_strings.text1);
    free(params.two_strings.text2);
    break;
  default:
    break;
  }

  return RETURN_CODE;
}
