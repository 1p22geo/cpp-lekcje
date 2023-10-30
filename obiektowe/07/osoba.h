#pragma once
#include <iostream>
using namespace std;

class Osoba{
    protected:
        string imie;
        string nazwizko;
        string dataUrodzenia;
    public:
        Osoba(string imie_, string nazwizko_, string dataUrodzenia_);
        void WypiszInfo();
};