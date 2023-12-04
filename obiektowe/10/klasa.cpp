#include "klasa.h"

Klasa::Klasa():x(0){}
Klasa::Klasa(int _x):x(_x){}

int Klasa::get_x(){
    return this->x;
}