#ifndef PLIKH
#include "plik.h"
#define PLIKH
#endif
#ifndef SAMOHUD
#include "samohud.h"
#define SAMOHUD
#endif
#include <iomanip>

Plik::Plik() : nazwa("default") { this->otwarty = false; }
Plik::Plik(string n) : nazwa(n) { this->otwarty = false; }

void Plik::otworz()
{
    this->plik.open(this->nazwa);
    if (this->plik.good())
    {
        this->otwarty = true;
    }
}

std::vector<Samohud> Plik::wczytaj()
{
    std::vector<Samohud> samochody;
    string marka;
    string model;
    string paliwo;
    float pojemnosc;
    string kolor;

    while (plik >> marka)
    {
        plik >> model;
        plik >> pojemnosc;
        plik >> paliwo;
        plik >> kolor;
        Kolor tmpKolor;
        if (kolor.at(0) == '#')
        {
            cout << "Kolor hex "<<kolor<<endl;
            string hstr = kolor.substr(1, 6);
            int r, g, b;
            sscanf(hstr.c_str(), "%02x%02x%02x", &r, &g, &b);
            cout <<'#'<< std::hex << std::setfill('0') <<std::setw(2) << r << g << b;
            tmpKolor.setKolor(r,g,b);
        }
        else
        {
            tmpKolor.setKolor(kolor);
        }
        Samohud autko(marka, model, pojemnosc, paliwo, tmpKolor);
        cout<<autko.to_string();
        samochody.push_back(autko);
    }

    return samochody;
}

void Plik::zapisz(std::vector<Samohud> samohody)
{
    if(this->otwarty){
        plik.close();
        otwarty = false;
    }
    plik.open(nazwa, ios::out);
    if (plik.good()){
        otwarty = true;
        for(auto samohud:samohody){
            plik <<samohud.getMarka()<<endl;
            plik <<samohud.getModel()<<endl;
            plik <<samohud.getPojemnosc()<<endl;
            plik <<samohud.getPaliwo()<<endl;
            plik <<samohud.getKolor().getKolor()<<endl;
        }
    }
}

string Plik::getNazwa(){
    return this->nazwa;
}
void Plik::setNazwa(string n){
    nazwa = n;
}