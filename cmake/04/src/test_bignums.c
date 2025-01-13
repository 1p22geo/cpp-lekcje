#include "asserts.h"
#include "bignums.h"
#include "bignums_debug.h"
#include <stddef.h>

int main() {
  assert(count_digits(0x01) == 1);
  assert(count_digits(0x43) == 1);
  assert(count_digits(0x57f2ac) == 3);
  assert(count_digits(0xffffffffff) == 5);
  assert(count_digits(0x10000000) == 4);
  assert(count_digits(0x00) == 1);

  dec n1 = int_to_dec(0xff00deadbeef);
  assert(n1.length == 6);
  assert(n1.point == 6);
  assert(n1.digits[0] == 0xff);
  assert(n1.digits[1] == 0x00);
  assert(n1.digits[2] == 0xde);
  assert(n1.digits[3] == 0xad);
  assert(n1.digits[4] == 0xbe);
  assert(n1.digits[5] == 0xef);

  assert(dec_to_int(n1) == 0xff00deadbeef);

  dec_dealloc(n1);

  dec n2 = double_to_dec(12.5); // 0C . 80
  assert(n2.length == 2);
  assert(n2.point == 1);
  assert(n2.digits[0] == 0x0C);
  assert(n2.digits[1] == 0x80);

  assert(dec_to_double(n2) == 12.5);

  dec_dealloc(n2);

  dec n3 = double_to_dec(1454125.14345);
  assert(dec_to_double(n3) == 1454125.14345);
  dec_dealloc(n3);
}
