#include "plik.h"
#include "samohud.h"
#include "kolor.h"
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
        Plik plik(nazwaPliku);
        plik.otworz();
        samochody = plik.wczytaj();
    }
    Samohud sam("fiat", "punto", 2.4, "diesel", Kolor(12, 254, 53));
    samochody.push_back(sam);
    for(auto samochod:samochody){
        cout<<samochod.to_string()<<endl;
    }
    plik.zapisz(samochody);
}