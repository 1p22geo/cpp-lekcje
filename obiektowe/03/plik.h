#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#ifndef SAMOHUD
#include "samohud.h"
#define SAMOHUD
#endif

using namespace std;

class Plik{
    private:
        string nazwa;
        fstream plik;
        bool otwarty;
    public:
        Plik(string n);
        string getNazwa();
        void setNazwa(string n);
        Plik();
        void otworz();
        std::vector<Samohud> wczytaj();
        void zapisz(std::vector<Samohud> samohody);
};