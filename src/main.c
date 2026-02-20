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

  char input[1024];
  printf("Enter your message: \n");
  scanf(" %1023[^\n]", input);

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

  free(result);

  return 0;
}
