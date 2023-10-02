/*
 *   PLIK NAGŁÓWKOWY
 *   DEKLARACJA KLASY Ryba()
 *
 * 
 */

#include <iostream>

using namespace std;

class Ryba{
    private:
        string gatunek;
        int rozmOchr;
        float waga;
    public:
        Ryba(string gatunek, int rozmOchr, float waga);
        //Ryba(Ryba &ryba);
        Ryba();
        ~Ryba();

        float getWaga();
        string getGatunek();
        int getRozmiar();

        void setWaga(float waga);
        string toString();
};