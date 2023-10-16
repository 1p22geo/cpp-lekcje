#pragma once
#include <iostream>
using namespace std;

class TKonto{
    public:
        string nazwa;
        TKonto();
        TKonto(string n, string num, float sld);
        string getNumer();
        void setNumer(string n);
        string toString();
        int wplata(float kwota);
        int wyplata(float kwota);
    private:
        string numer;
        float saldo;
};