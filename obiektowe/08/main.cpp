#include "pies.h"
#include "kot.h"

#include <iostream>
#include <string.h>

using namespace std;

int main(){
    Kot kotek(5, "Bob");
    Pies piesek(2020, "paweu");
    kotek.przedstawSie();
    piesek.przedstawSie();


    return 0;
}