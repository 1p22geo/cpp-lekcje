#pragma once
#include "figura.h"
#include <cmath>
#include <string>

class TrojkatRownoboczny: public Figura{
    protected:
        float bok;
        std::string nazwa;
    public:
        TrojkatRownoboczny(float _bok, std::string _nazwa);
        void obliczPole();
        void obliczObwod();
        std::string info();
};