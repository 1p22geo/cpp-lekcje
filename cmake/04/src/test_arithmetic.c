#include "asserts.h"
#include "bignums.h"
#include "bignums_debug.h"
#include <stddef.h>

int main() {
  double double_a_1 = 14143432.14155425;
  double double_b_1 = 121.15515561514;

  dec dec_a_1 = double_to_dec(double_a_1);
  dec dec_b_1 = double_to_dec(double_b_1);

  dec sum_1 = dec_add(dec_a_1, dec_b_1);

  assert(dec_to_double(sum_1) == double_a_1 + double_b_1);

  dec_dealloc(sum_1);

  dec_dealloc(dec_a_1);
  dec_dealloc(dec_b_1);
}
