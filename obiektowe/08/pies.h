#pragma once

#include "zwierze.h"

class Kot;


class Pies : public  Zwierze {
    protected:
        int rok_ur;
    public:
        Pies();
        Pies(int _rok_ur, string _nazwa);
        void przedstawSie();
    friend void ktoStarszy(Kot, Pies);
};