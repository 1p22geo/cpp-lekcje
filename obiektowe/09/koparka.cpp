#include "koparka.h"

Koparka::Koparka()
{
    this->moc = 0;
}

Koparka::Koparka(float _moc,  std::string _nazwa, int _rocznik):Pojazd(_nazwa,_rocznik)
{
    this->moc = _moc;
}

float Koparka::getMoc()
{
    return this->moc;
}

std::string Koparka::info()
{
    return std::string("koparka "+this->nazwa + ", rocznik " + std::to_string(this->rocznik)+ ", moc " + std::to_string(this->moc) + " wat");
}
