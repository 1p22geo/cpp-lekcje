#pragma once
#include <iostream>
#include "../pilkarz.h"
#include "../osoba.h"

class PilkarzNozny: public Pilkarz{
    public:
        PilkarzNozny(string imie_, string nazwizko_, string dataUrodzenia_,string pozycja_, string klub_);
        void StrzelGola();
};