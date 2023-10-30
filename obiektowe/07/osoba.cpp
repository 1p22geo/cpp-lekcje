#include "osoba.h"

Osoba::Osoba(string imie_, string nazwizko_, string dataUrodzenia_)
{
    this->imie = imie_;
    this->nazwizko = nazwizko_;
    this->dataUrodzenia = dataUrodzenia_;
}

void Osoba::WypiszInfo()
{
    std::cout << "imie: " << this->imie << endl;
    std::cout << "nazwizko: " << this->nazwizko << endl;
    std::cout << "urodzony: " << this->dataUrodzenia << endl;
}
