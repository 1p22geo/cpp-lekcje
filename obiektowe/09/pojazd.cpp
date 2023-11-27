#include "pojazd.h"

Pojazd::Pojazd()
{
    this->nazwa = "undefined";
    this->rocznik = 2000;
}

Pojazd::Pojazd(std::string _nazwa, int _rocznik){
    this->nazwa = _nazwa;
    this->rocznik = _rocznik;
}

std::string Pojazd::getNazwa()
{
    return std::string(this->nazwa);
}

int Pojazd::getRocznik()
{
    return this->rocznik;
}

std::string Pojazd::info()
{
    return std::string(this->nazwa + ", " + std::to_string(this->rocznik));
}
