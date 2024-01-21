#include "czas.h"

Czas::Czas(unsigned long _minuty) : minuty(_minuty) {}

Czas::Czas(unsigned long _godziny, unsigned long _minuty) : minuty(_minuty + _godziny * 60) {}

std::string Czas::ToString()
{
    std::stringstream ss;
    ss<<minuty/60;
    ss<<":";
    ss<<minuty%60;
    
    return std::string(ss.str());
}

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
