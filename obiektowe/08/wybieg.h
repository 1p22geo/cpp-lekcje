#pragma once;
#include "zwierze.h"

class Wybieg {
    private:
        int maxIlosc;
        int ilosc;
        Zwierze *wybieg;
    public:
        Wybieg();
        Wybieg(int _maxIlosc);
        void add(Zwierze &z);
        void print();
};