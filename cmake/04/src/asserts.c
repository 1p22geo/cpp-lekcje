#include "asserts.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void assert_msg(bool cond, char *text) {
  if (!cond) {
    if (text != NULL) {
      fprintf(stderr, "Assertion failed: %s", text);
    } else {
      fprintf(stderr, "Assertion failed.");
    }
    exit(1);
  }
}
void assert(bool cond) {
  if (!cond) {
    fprintf(stderr, "Assertion failed.");
    exit(1);
  }
}
