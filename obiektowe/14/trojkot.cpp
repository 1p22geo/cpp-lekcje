#include "trojkot.h"

float pole_trojkota(int a, int b, int c)
{
    if( (a+b<=c)||(a+c<=b)||(c+b<=a) ){
        throw TrojkotWyjotek(a,b,c);
    }
    float p = (a+b+c)/2.0;
    float S = sqrt(p * (p-a) * (p-b) * (p-c));
    return S;
}