#include "bignums.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

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
  c.point = c.length - point;

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

  b /= pow(256, a.length - a.point);
  return b;
}

dec dec_add(dec a, dec b) {
  dec c;
  uint64_t digits_bce;
  uint64_t digits_ce;
  uint64_t a_l_offset;
  uint64_t b_l_offset;
  uint64_t a_r_offset;
  uint64_t b_r_offset;
  int32_t carry;
  uint16_t a_digit;
  uint16_t b_digit;

  digits_bce = a.point > b.point ? a.point : b.point;
  if (a.point == b.point &&
      ((uint16_t)a.digits[0] + (uint16_t)b.digits[0] > 256)) {
    // carry on the first digit
    digits_bce++;
  }

  digits_ce = a.length - a.point > b.length - b.point ? a.length - a.point
                                                      : b.length - b.point;

  a_l_offset = digits_bce - a.point;
  b_l_offset = digits_bce - b.point;
  a_r_offset = (digits_ce - (a.length - a.point));
  b_r_offset = (digits_ce - (b.length - b.point));

  c.length = digits_bce + digits_ce;
  c.point = digits_bce;
  c.digits = malloc(c.length);

  carry = 0;
  for (int i = 0; i < digits_ce; i++) {
    a_digit =
        ((a_r_offset <= i) ? (a.digits[a.length - i - 1 + a_r_offset]) : 0);
    b_digit =
        ((b_r_offset <= i) ? (b.digits[b.length - i - 1 + b_r_offset]) : 0);

    c.digits[c.length - i - 1] = a_digit + b_digit + carry;

    carry = (a_digit + b_digit + (uint16_t)carry) / 256;
  }

  for (int i = digits_bce - 1; i >= 0; i--) {
    a_digit = ((a_l_offset <= i) ? (a.digits[i - a_l_offset]) : 0);
    b_digit = ((a_r_offset <= i) ? (b.digits[i - b_l_offset]) : 0);

    c.digits[i] = a_digit + b_digit + carry;

    carry = (a_digit + b_digit + (uint16_t)carry) / 256;
  }

  return c;
}

void dec_dealloc(dec number) { free(number.digits); }
