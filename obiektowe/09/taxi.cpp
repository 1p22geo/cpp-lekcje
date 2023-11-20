#include "taxi.h"

Taxi::Taxi()
{
    this->miejsca = 4;
}
Taxi::Taxi(int _miejsc){
    this->miejsca = _miejsc;
}

int Taxi::getMiejsca()
{
    return this->miejsca;
}
