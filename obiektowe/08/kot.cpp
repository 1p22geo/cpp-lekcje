#include "kot.h"

Kot::Kot()
{
    this->nazwa = "bezimienny kotek";
    this->lata = 0;
}

Kot::Kot(int _lata, string _nazwa)
{
    this->nazwa = _nazwa;
    this->lata = _lata;
}

void Kot::przedstawSie()
{
    std::cout<< "Kot o imieniu " << nazwa << ", ma " << lata << " lat\n";
}
