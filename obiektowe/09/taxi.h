#pragma once
#include <string>
#include "pojazd.h"

class Taxi : public Pojazd {
    protected:
        int miejsca;
    public:
        Taxi();
        Taxi(int _miejsc, std::string nazwa, int rocznik);
        int getMiejsca();
        std::string info();
};