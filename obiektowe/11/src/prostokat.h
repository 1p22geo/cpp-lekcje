#pragma once
#include "figura.h"
#include <cmath>
#include <string>

class Prostokat: public Figura{
    protected:
        float a;
        float b;
        std::string nazwa;
    public:
        Prostokat(float _a, float _b, std::string _nazwa);
        void obliczPole();
        void obliczObwod();
        std::string info();
        static Prostokat* kwadrat(float _a, std::string _nazwa);
};