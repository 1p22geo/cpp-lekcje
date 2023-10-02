#include "ryba.h"
#include <string>

Ryba::Ryba(string gatunek_, int rozmOchr_, float waga_){
    this->gatunek = gatunek_;
    this->rozmOchr = rozmOchr_;
    this->waga = waga_;
}
Ryba::Ryba(){
    this->gatunek = "brak informacji";
    this->rozmOchr = 0;
    this->waga = 0;
}
string Ryba::getGatunek(){
    return this->gatunek;
}
int Ryba::getRozmiar(){
    return  this->rozmOchr;
}
float Ryba::getWaga(){
    return this->waga;
}
void Ryba::setWaga(float w){
    this->waga = w;
}
string Ryba::toString(){
    string napis = "RYBA:";
    napis += "\n\tgatunek: " + gatunek;
    napis += "\n\twaga: " + to_string(waga);
    napis += "\n\trozmiar ochronny: " + to_string(rozmOchr);
    return napis;
}


Ryba::~Ryba(){
    cout<<"Ryba "<<gatunek<<" padla"<<endl;
    delete &this->gatunek;
    delete &this->rozmOchr;
    delete &this->waga;
}