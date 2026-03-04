#include "ciphers/polybius_square.h"
#include "cipher.h"
#include <stdlib.h>
#include <string.h>

// Assumes input values from 0 to 9 only
inline static char num_to_char(int num) { return (char)('0' + num); }
inline static int char_to_num(char ch) { return (int)(ch - '0'); }

// Case is lost
static int substitute(char ch) {
  int idx;
  if ('a' <= ch && ch <= 'z')
    idx = ch - 'a';
  else if ('A' <= ch && ch <= 'Z')
    idx = ch - 'A';
  else
    return -1;

  if (idx >= 'j' - 'a')
    idx--;

  return (idx / 5 + 1) * 10 + idx % 5 + 1;
}

// Case is not recoverable
static char inverse_substitute(int num) {
  int idx = (num / 10 - 1) * 5 + num % 10 - 1;
  if (idx >= 'j' - 'a')
    idx++;
  return 'a' + idx;
}

char *polybius_square_encrypt(const char *input,
                              const cipher_params_t *params) {
  (void)params;

  size_t len = strlen(input);

  char *output = malloc(len * 3 + 1);
  if (!output)
    return NULL;

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    int num = substitute(input[i]);
    if (num != -1) {
      output[j++] = num_to_char(num / 10);
      output[j++] = num_to_char(num % 10);
      output[j++] = ' ';
    } else {
      output[j++] = input[i];
      output[j++] = ' ';
    }
  }

  if (j > 0)
    j--;
  output[j] = '\0';

  return output;
}

char *polybius_square_decrypt(const char *input,
                              const cipher_params_t *params) {
  (void)params;

  size_t len = strlen(input);

  while (len > 0 && *input == ' ') {
    input++;
    len--;
  }

  char *output = malloc((len + 1) / 2 + 1);
  if (!output)
    return NULL;

  size_t i = 0, j = 0;
  while (i < len) {
    if (i + 1 == len || input[i + 1] == ' ') {
      output[j++] = input[i];
      i += 2;
    } else if (('0' <= input[i] && input[i] <= '9') &&
               ('0' <= input[i + 1] && input[i + 1] <= '9')) {
      int num = char_to_num(input[i]) * 10 + char_to_num(input[i + 1]);
      char ch = inverse_substitute(num);
      output[j++] = ch;
      i += 3;
    } else {
      output[j++] = input[i];
      i++;
    }
  }

  output[j] = '\0';

  return output;
}
