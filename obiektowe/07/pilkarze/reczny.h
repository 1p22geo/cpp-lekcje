#pragma once
#include <iostream>
#include "../pilkarz.h"
#include "../osoba.h"

class PilkarzReczny: public Pilkarz{
    public:
        PilkarzReczny(string imie_, string nazwizko_, string dataUrodzenia_,string pozycja_, string klub_);
        void StrzelGola();
};