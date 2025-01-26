#include <stdint.h>

#ifndef BIGNUMS_H
#define BIGNUMS_H

typedef enum {
  POSITIVE,
  NEGATIVE,
  INVALID,
} dec_sign;

/*
Base-256 decimal number.
(decimal? 256-imal?)

Array of digits as bytes,
position of decimal point from first byte,
and length (number of bytes)
*/

typedef struct {
  uint8_t *digits;
  uint64_t point;
  uint64_t length;
  dec_sign sign;
} dec;

// mallocs memory on the heap.
// You are responsible for freeing it.
// See: dec_dealloc()
dec int_to_dec(uint64_t number);

// May lose some digits.
// Cuts out decimal part, does not round.
uint64_t dec_to_int(dec number);

// Same as int_to_dec.
dec double_to_dec(double number);

// May lose precision.
double dec_to_double(dec number);

// free-s the digits array.
// You are responsible for discarding the struct afterwards.
void dec_dealloc(dec number);

// arithmetic operations
dec dec_add(dec a, dec b);
dec dec_sub(dec a, dec b);
dec dec_mul(dec a, dec b);
dec dec_div(dec a, dec b);
dec dec_pow(dec a, dec b);

// counts the base-256 digits of an int
uint64_t count_digits(uint64_t num);

int8_t dec_cmp(dec a, dec b);

#define dec_flip(c) c.sign = c.sign == NEGATIVE ? POSITIVE : NEGATIVE;

#endif // BIGNUMS_H
