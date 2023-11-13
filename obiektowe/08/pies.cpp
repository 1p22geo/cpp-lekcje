#include "pies.h"

Pies::Pies()
{
    this->nazwa = "bezimienny kotek";
    this->rok_ur = 2023;
}

Pies::Pies(int _rok_ur, string _nazwa)
{
    this->nazwa = _nazwa;
    this->rok_ur = _rok_ur;
}

void Pies::przedstawSie()
{
    std::cout<< "Pies o imieniu " << nazwa << ", urodzony w " << rok_ur << " roku\n";
}
