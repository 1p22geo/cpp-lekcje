#include "kolor.h"
#include <iomanip>
using namespace std;

Kolor::Kolor(string k){
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
        stream <<'#'<< std::hex << this->R << this->G << this->B;
        std::string result( stream.str() );
        return result;
    }
    else{
        return this->nazwa;
    }
}