#include "czas.h"

Czas::Czas(unsigned long _minuty) : minuty(_minuty) {}

Czas::Czas(unsigned long _godziny, unsigned long _minuty) : minuty(_minuty + _godziny * 60) {}

std::string Czas::ToString() { return std::string(std::to_string(minuty / 60) + ":" + std::to_string(minuty % 60)); }

Czas Czas::operator+(Czas &that)
{
    return Czas(this->minuty + that.minuty);
}
Czas Czas::operator-(Czas &that)
{
    if (this->minuty > that.minuty)
    {
        return Czas(this->minuty - that.minuty);
    }
    return Czas(0);
}

bool Czas::operator>(Czas &that)
{
    return this->minuty > that.minuty;
}
