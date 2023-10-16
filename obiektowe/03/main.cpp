#ifndef PLIKH
#include "plik.h"
#define PLIKH
#endif
#ifndef SAMOHUD
#include "samohud.h"
#define SAMOHUD
#endif
#ifndef KOLORH
#include "kolor.h"
#define KOLORH
#endif
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
    cout<<"Witam w salonie samochodowym"<<endl;
    cout<<"Prosze podac nazwe pliku"<<endl;
    string nazwaPliku;
    vector<Samohud> samochody;
    Plik plik;
    cin>>nazwaPliku;
    if ((nazwaPliku != "" )&& (nazwaPliku != "BRAK")){
        cout<<nazwaPliku<<endl;
        cout << &plik<<endl;
        plik.setNazwa(nazwaPliku);
        cout << plik.getNazwa()<<endl;
        cout << &plik<<endl;
        plik.otworz();
        samochody = plik.wczytaj();
    }
    cout << plik.getNazwa()<<endl;
    Samohud sam("fiat", "punto", 2.4, "diesel", Kolor(12, 254, 53));
    samochody.push_back(sam);
    for(auto samochod:samochody){
        cout<<samochod.to_string()<<endl;
    }
    plik.zapisz(samochody);
}