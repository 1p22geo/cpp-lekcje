#include <stdbool.h>

#ifndef ASSERTS_H
#define ASSERTS_H

void assert_msg(bool cond, char *text);
void assert(bool cond);

#endif
