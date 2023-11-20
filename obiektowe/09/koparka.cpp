#include "koparka.h"

Koparka::Koparka()
{
    this->moc = 0;
}

Koparka::Koparka(float _moc)
{
    this->moc = _moc;
}

float Koparka::getMoc()
{
    return this->moc;
}
