#include "bignums.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t count_digits(uint64_t num) {
  uint64_t digits;

  if (num == 0)
    return 1;

  digits = 0;

  while (num != 0) {
    num -= num % 256;
    num = num / 256;
    digits += 1;
  }

  return digits;
}

dec double_to_dec(double a) {
  uint64_t b;
  dec c;
  uint64_t point = 0;

  while (floor(a) != a) {
    // while this could loop infinitely on a real number,
    // it's just a double :3
    point++;
    a *= 256;
  }

  b = a; // after scaling it up, convert to an int

  c = int_to_dec(a);
  c.point = point;

  return c;
}

dec int_to_dec(uint64_t a) {
  uint64_t num_digits;
  dec b;

  num_digits = count_digits(a);

  b.length = num_digits;
  b.point = num_digits;
  b.digits = malloc(num_digits);

  for (int n = 1; n < num_digits + 1; n++) {
    b.digits[num_digits - n] = a % 256;
    a /= 256;
  }
  return b;
}

uint64_t dec_to_int(dec a) {
  uint64_t b = 0;
  for (int n = 0; n < a.point; n++) {
    b *= 256;
    b += a.digits[n];
  }

  return b;
}

double dec_to_double(dec a) {
  double b = 0;
  for (int n = 0; n < a.length; n++) {
    b *= 256;
    b += a.digits[n];
  }

  b /= pow(256, a.point);
  return b;
}

void dec_dealloc(dec number) { free(number.digits); }
