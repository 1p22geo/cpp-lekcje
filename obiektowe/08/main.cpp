#include "pies.h"
#include "kot.h"

#include <iostream>
#include <string.h>

using namespace std;

int main(){
    Kot kotek(5, "Bob");
    Pies piesek = *new Pies();
    kotek.przedstawSie();
    piesek.przedstawSie();


    return 0;
}