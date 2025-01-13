#include <stdio.h>

#define PRINTDEC_HEX(dec)                                                      \
  for (int i = 0; i < dec.length; i++) {                                       \
    if (i == dec.point)                                                        \
      printf(".");                                                             \
    printf("%02x ", dec.digits[i]);                                            \
  }                                                                            \
  printf("\n");

#define PRINTDEC_DEC(dec)                                                      \
  for (int i = 0; i < dec.length; i++) {                                       \
    if (i == dec.point)                                                        \
      printf(".");                                                             \
    printf("%03d ", dec.digits[i]);                                            \
  }                                                                            \
  printf("\n");
