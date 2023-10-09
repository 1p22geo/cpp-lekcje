#include "samohud.h"
#include <iomanip>
#include <iostream>
using namespace std;

Samohud::Samohud(){
    
    this->marka = "brak danych";
    this->model = "brak danych";
    this->paliwo = "brak danych";
    this->pojemnosc = 0;
    this->kolor = *(new Kolor("brak danych"));
}

Samohud::Samohud(string mar, string mod, float poj, string pal, Kolor kol){
    this->marka = mar;
    this->model = mod;
    this->paliwo = pal;
    this->pojemnosc = poj;
    this->kolor = kol;
}

string Samohud::getMarka(){
    return this->marka;
}
string Samohud::getModel(){
    return this->model;
}
float Samohud::getPojemnosc(){
    return this->pojemnosc;
}
string Samohud::getPaliwo(){
    return this->paliwo;
}
Kolor Samohud::getKolor(){
    return this->kolor;
}

string Samohud::to_string(){
    std::stringstream stream;
    stream  << "SAMOHUD ->"<<endl
            << "\t" <<this->marka <<" " <<this->model <<endl
            << "\t" <<"silnik" <<" " <<this->pojemnosc <<" l" <<endl
            << "\t"<<this->paliwo <<endl
            << "\t" <<"koloru:" <<" " <<this->kolor.getKolor()<<endl
    ;
    
    std::string result( stream.str() );
    return result;
}