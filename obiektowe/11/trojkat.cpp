#include "trojkat.h"
#include "figura.h"


TrojkatRownoboczny::TrojkatRownoboczny(float _bok, std::string _nazwa)
{
    this->bok = _bok;
    this->nazwa = _nazwa;
}

void TrojkatRownoboczny::obliczPole()
{
    this->pole = pow(this->bok, 2)*sqrt(3)*1/4;
}

void TrojkatRownoboczny::obliczObwod()
{
    this->obwod = this->bok * 3;
}

std::string TrojkatRownoboczny::info()
{
    return "trojkat o polu "+ std::to_string(this->pole)+" , obwodzie "+std::to_string(this->obwod)+" i nazwie \""+this->nazwa+"\"";
}
