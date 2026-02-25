#include "cipher.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum operation { ENCRYPT, DECRYPT };

int main(void) {

  printf("Operations: \n1. Encrypt\n2. Decrypt\nChoose the operation: ");
  int operation;
  scanf("%d", &operation);
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
  scanf("%d", &cipher_id);
  cipher_id--;

  const cipher_t *cipher = get_cipher(cipher_id);
  if (!cipher) {
    printf("Invalid cipher id\n");
    return 1;
  }

  int c, prev = 0, len = 0, cap = 16;
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

  cipher_params_t params = {0};
  char keyword[128];
  params.string = keyword;

  switch (cipher->param_type) {
  case PARAM_NONE:
    break;

  case PARAM_NUMBER:
    printf("Enter the key: ");
    scanf("%d", &params.number);
    break;

  case PARAM_2_NUMBERS:
    printf("Enter the number 1: ");
    scanf("%d", &params.number);
    printf("Enter the number 2: ");
    scanf("%d", &params.number2);
    break;

  case PARAM_STRING:
    printf("Enter the keyword: ");
    scanf("%127s", params.string);
    break;
  }

  char *result;
  if (operation == ENCRYPT) {
    result = cipher->encrypt(input, &params);
  } else {
    result = cipher->decrypt(input, &params);
  }
  if (!result) {
    printf("Operation failed\n");
    return 1;
  }
  printf("Result:\n%s\n", result);

  free(input);
  free(result);

  return 0;
}
