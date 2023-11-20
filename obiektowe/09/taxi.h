#pragma once
#include <string>
#include "pojazd.h"

class Taxi : public Pojazd {
    protected:
        int miejsca;
    public:
        Taxi();
        Taxi(int _miejsc);
        int getMiejsca();
};