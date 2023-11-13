#pragma once

#include "zwierze.h"

class Pies;

class Kot : public Zwierze {
    protected:
        int lata;
    public:
        Kot();
        Kot(int _lata, string _nazwa);
        void przedstawSie();
    friend void ktoStarszy(Kot, Pies);
};