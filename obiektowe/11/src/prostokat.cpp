#include "prostokat.h"

Prostokat::Prostokat(float _a, float _b, std::string _nazwa)
{
    this->a = _a;
    this->b = _b;
    this->nazwa = _nazwa;
}

void Prostokat::obliczPole()
{
    this->pole = this->a * this->b;
}

void Prostokat::obliczObwod()
{
    this->obwod = 2*this->a + 2*this->b;
}

std::string Prostokat::info()
{
    return "prostokat o polu "+ std::to_string(this->pole)+" , obwodzie "+std::to_string(this->obwod)+" i nazwie \""+this->nazwa+"\"";
}

Prostokat *Prostokat::kwadrat(float _a, std::string _nazwa)
{
    return new Prostokat(_a, _a, _nazwa);
}
