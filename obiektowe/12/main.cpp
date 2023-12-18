#include <iostream>
#include "vector.h"

int main(){
    Vector vec1(12, 0.1);
    Vector vec2(0.4, 14);
    Vector vec = vec1 + vec2;
    Vector vec3 = vec;
    std::cout<<vec3.to_string();
    return 0;
}