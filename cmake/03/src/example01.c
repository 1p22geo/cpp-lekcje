#include <math.h>
#include <stdio.h>
int main() {
  float i = 1000;
  float tempResult = ((1 / i) + 1);
  float result = pow(tempResult, i);
  printf("a_%f = %f\n", i, result);
  return 0;
  /*

    (1 + 1/n) ^ n

    ((n+1)/(n))^n

    (n+1)^n / (n)^n

    we need to calculate (n+1)^n and then n^n
    and then divide

  */
}
