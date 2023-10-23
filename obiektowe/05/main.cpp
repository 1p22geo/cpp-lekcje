#include "baseA.h"
#include "childA.h"
#include <iostream>

int main(){
    ChildA bsA("pbA", "cA", "prA");
    bsA.pubA = "public baseA";
    std::cout <<bsA.info();
    std::cout << bsA.getPrtA();
    return 0;
} 