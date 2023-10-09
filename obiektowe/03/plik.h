#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "samohud.h"

using namespace std;

class Plik{
    private:
        string nazwa;
        fstream plik;
        bool otwarty;
    public:
        Plik(string n);
        Plik();
        void otworz();
        std::vector<Samohud> wczytaj();
        void zapisz(std::vector<Samohud> samohody);
};