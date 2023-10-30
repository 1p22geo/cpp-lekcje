#pragma once
#include <iostream>
#include "osoba.h"

using namespace std;

class Pilkarz: Osoba{
    private:
        string pozycja;
        string klub;
        int liczbaGoli = 0;
    public:
        Pilkarz(string imie_, string nazwizko_, string dataUrodzenia_,string pozycja_, string klub_);
        void WypiszInfo();
        void StrzelGola();
};