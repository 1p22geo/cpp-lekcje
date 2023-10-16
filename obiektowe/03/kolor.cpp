#ifndef KOLORH
#include "kolor.h"
#define KOLORH
#endif
#include <iomanip>
using namespace std;

void Kolor::setKolor(int r, int g, int b)
{
    this->R = r;
    this->G = g;
    this->B = b;
    this->hex = true;
}

void Kolor::setKolor(string n)
{
    this->nazwa = n;
    this->hex = false;
}

Kolor::Kolor(string k)
{
    this->nazwa = k;
    this->hex = false;
}

Kolor::Kolor(int r, int g, int b){
    this->R = r;
    this->G = g;
    this->B = b;
    this->hex = true;
}

Kolor::Kolor(){
    this->nazwa = "przezroczysty taki";
    this->hex = false;
}

string Kolor::getKolor(){
    if(this->hex){
        std::stringstream stream;
        stream <<'#'<< std::hex << std::setfill('0') <<std::setw(2) << this->R << this->G << this->B;
        std::string result( stream.str() );
        return result;
    }
    else{
        return this->nazwa;
    }
}