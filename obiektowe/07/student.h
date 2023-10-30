#pragma once
#include <iostream>
#include "osoba.h"
using namespace std;

class Student : public Osoba{
    private:
        int rok;
        int grupa;
        int nrIndeksu;
    public:
        Student(string imie_, string nazwizko_, string dataUrodzenia_, int rok_, int grupa_, int nrIndeksu_);
        void WypiszInfo();
};