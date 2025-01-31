#include "bignums.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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

  b = fabs(a); // after scaling it up, convert to an uint

  c = int_to_dec(b);
  c.sign = a >= 0 ? POSITIVE : NEGATIVE;
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

  if (a.sign == NEGATIVE)
    b *= -1;

  return b;
}

dec udec_add(dec a, dec b) {
  if (a.sign == NEGATIVE || b.sign == NEGATIVE) {
    dec c;
    c.sign = INVALID;
    return c;
  }

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

dec udec_sub(dec a, dec b) {
  if (a.sign == NEGATIVE || b.sign == NEGATIVE) {
    dec c;
    c.sign = INVALID;
    return c;
  }

  dec c;
  uint64_t digits_bce;
  uint64_t digits_ce;
  uint64_t a_l_offset;
  uint64_t b_l_offset;
  uint64_t a_r_offset;
  uint64_t b_r_offset;
  int32_t borrow;
  uint16_t a_digit;
  uint16_t b_digit;

  // Determine the number of digits before the decimal point
  digits_bce = a.point > b.point ? a.point : b.point;
  if (a.point == b.point &&
      ((uint16_t)a.digits[0] - (uint16_t)b.digits[0] < 0)) {
    // borrow on the first digit
    digits_bce++;
  }

  // Determine the number of digits after the decimal point
  digits_ce = a.length - a.point > b.length - b.point ? a.length - a.point
                                                      : b.length - b.point;

  // Calculate offsets for a and b
  a_l_offset = digits_bce - a.point;
  b_l_offset = digits_bce - b.point;
  a_r_offset = (digits_ce - (a.length - a.point));
  b_r_offset = (digits_ce - (b.length - b.point));

  // Initialize result
  c.length = digits_bce + digits_ce;
  c.point = digits_bce;
  c.digits = malloc(c.length);

  // Initialize borrow
  borrow = 0;

  // Subtract digits after the decimal point
  for (int i = 0; i < digits_ce; i++) {
    a_digit =
        ((a_r_offset <= i) ? (a.digits[a.length - i - 1 + a_r_offset]) : 0);
    b_digit =
        ((b_r_offset <= i) ? (b.digits[b.length - i - 1 + b_r_offset]) : 0);

    c.digits[c.length - i - 1] = a_digit - b_digit - borrow;

    if (a_digit - b_digit - borrow < 0) {
      c.digits[c.length - i - 1] += 256;
      borrow = 1;
    } else {
      borrow = 0;
    }
  }

  // Subtract digits before the decimal point
  for (int i = digits_bce - 1; i >= 0; i--) {
    a_digit = ((a_l_offset <= i) ? (a.digits[i - a_l_offset]) : 0);
    b_digit = ((b_l_offset <= i) ? (b.digits[i - b_l_offset]) : 0);

    c.digits[i] = a_digit - b_digit - borrow;

    if (a_digit - b_digit - borrow < 0) {
      c.digits[i] += 256;
      borrow = 1;
    } else {
      borrow = 0;
    }
  }

  // Check if the result is negative
  if (borrow == 1) {
    c.sign = NEGATIVE;
    // Add the absolute value of b to a
    dec temp = dec_add(a, b);
    free(c.digits);
    c.digits = temp.digits;
    c.length = temp.length;
    c.point = temp.point;
  } else {
    c.sign = POSITIVE;
  }

  return c;
}

dec dec_add(dec a, dec b) {
  if (a.sign == POSITIVE && b.sign == POSITIVE) {
    return udec_add(a, b);
  }
  if (a.sign == POSITIVE && b.sign == NEGATIVE) {
    b.sign = POSITIVE;
    return udec_sub(a, b);
  }
  if (a.sign == NEGATIVE && b.sign == POSITIVE) {
    a.sign = POSITIVE;
    dec c = udec_sub(a, b);
    dec_flip(c);
    return c;
  }
  if (a.sign == NEGATIVE && b.sign == NEGATIVE) {
    a.sign = POSITIVE;
    b.sign = POSITIVE;
    dec c = udec_add(a, b);
    dec_flip(c);
    return c;
  }
  dec c;
  c.sign = INVALID;
  return c;
}

dec dec_sub(dec a, dec b) {
  dec_flip(b);

  return dec_add(a, b);
}

dec udec_mul(dec a, dec b) {
  if (a.length == 1 && a.digits[0] == 0 || b.length == 1 && b.digits[0] == 0) {
    dec result = {0};
    result.sign = POSITIVE;
    return result;
  }

  if (a.length <= 8 || b.length <= 8) {
    // sowwy :3
    return double_to_dec(dec_to_double(a) * dec_to_double(b));
  }

  uint64_t mid_a = a.length / 2;
  uint64_t mid_b = b.length / 2;

  dec a_high, a_low, b_high, b_low;
  a_high.digits = a.digits;
  a_high.length = a.length - mid_a;
  a_high.point = a.point + mid_a;
  a_low.digits = a.digits + mid_a;
  a_low.length = mid_a;
  a_low.point = a.point;

  b_high.digits = b.digits;
  b_high.length = b.length - mid_b;
  b_high.point = b.point + mid_b;
  b_low.digits = b.digits + mid_b;
  b_low.length = mid_b;
  b_low.point = b.point;

  dec p1 = udec_mul(a_high, b_high);
  dec p2 = udec_mul(a_low, b_low);
  dec p3 = udec_mul(dec_add(a_high, a_low), dec_add(b_high, b_low));
  dec p4 = dec_sub(p3, dec_add(p1, p2));

  dec result;
  result.length = p1.length + p2.length + p4.length;
  result.point = a.point + b.point;
  result.digits = malloc(result.length * sizeof(uint8_t));
  memcpy(result.digits, p1.digits, p1.length * sizeof(uint8_t));
  memcpy(result.digits + p1.length, p4.digits, p4.length * sizeof(uint8_t));
  memcpy(result.digits + p1.length + p4.length, p2.digits,
         p2.length * sizeof(uint8_t));
  result.sign = POSITIVE;

  while (result.length > 1 && result.digits[0] == 0) {
    memmove(result.digits, result.digits + 1,
            (result.length - 1) * sizeof(uint8_t));
    result.length--;
    result.point--;
  }

  dec_dealloc(p1);
  dec_dealloc(p2);
  dec_dealloc(p3);
  dec_dealloc(p4);

  return result;
}

dec dec_mul(dec a, dec b) {
  // not yet.
  return udec_mul(a, b);
}

void dec_dealloc(dec number) { free(number.digits); }
