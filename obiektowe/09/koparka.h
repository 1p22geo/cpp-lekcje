#pragma once
#include <string>
#include "pojazd.h"

class Koparka : public Pojazd {
    protected:
        float moc;
    public:
        Koparka();
        Koparka(float _moc,  std::string nazwa, int rocznik);
        float getMoc();
        std::string info();
};