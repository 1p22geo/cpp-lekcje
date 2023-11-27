#include "taxi.h"

Taxi::Taxi()
{
    this->miejsca = 4;
}
Taxi::Taxi(int _miejsc, std::string _nazwa, int _rocznik):Pojazd(_nazwa, _rocznik){
    this->miejsca = _miejsc;
}

int Taxi::getMiejsca()
{
    return this->miejsca;
}

std::string Taxi::info()
{
    return std::string("taxi "+this->nazwa + ", rocznik " + std::to_string(this->rocznik) + " z " + std::to_string(this->miejsca) + " siedzeniami");
}
