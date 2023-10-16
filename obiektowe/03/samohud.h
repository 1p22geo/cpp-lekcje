#include <iostream>
using namespace std;
#ifndef KOLORH
#include "kolor.h"
#define KOLORH
#endif



class Samohud{
    private:
        string marka;
        string model;
        float pojemnosc;
        string paliwo;
        Kolor kolor;
    public:
        Samohud();
        Samohud(string mar, string mod, float poj, string pal, Kolor kol);
        string getMarka();
        string getModel();
        float getPojemnosc();
        string getPaliwo();
        Kolor getKolor();
        string to_string();
};