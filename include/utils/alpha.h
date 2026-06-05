#ifndef UTILS_ALPHA_H
#define UTILS_ALPHA_H

#include <stdbool.h>
#include <stddef.h>

enum { NOT_ALPHABETIC = -1, NOT_NUMERIC = -2 };

int alpha_index(char ch);
int digit_value(char ch);

bool has_alpha(const char *str, size_t len);
bool has_num(const char *str, size_t len);

// Assumes input values from 0 to 9 only
static inline char num_to_char(int num) { return (char)('0' + num); }

// Use digit_value(char ch) if ch is not
// garaunteed to be within '0' to '9'
static inline int char_to_num(char ch) { return (int)(ch - '0'); }

#endif // UTILS_ALPHA_H
