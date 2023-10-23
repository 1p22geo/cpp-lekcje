#include "amfibia.h"
#include "boat.h"
#include "auto.h"
#include <iostream>

int main(){
    Amphibian amp(false, 3, false);
    std::cout<<amp.info();
    return 0;
}