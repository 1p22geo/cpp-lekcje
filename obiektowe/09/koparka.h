#pragma once
#include <string>
#include "pojazd.h"

class Koparka : public Pojazd {
    protected:
        float moc;
    public:
        Koparka();
        Koparka(float _moc);
        float getMoc();
};