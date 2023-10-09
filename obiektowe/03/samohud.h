#include <iostream>
#include "kolor.h"
using namespace std;




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