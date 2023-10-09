#include "plik.h"

Plik::Plik(string n) : nazwa(n) { this->otwarty = false; }
Plik::Plik() : nazwa("default") { this->otwarty = false; }

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
            string hstr = kolor.substr(1, 6);
            int r, g, b;
            sscanf(hstr.c_str(), "%02x%02x%02x", &r, &g, &b);
            Kolor tmpKolor(r, g, b);
        }
        else
        {
            Kolor tmpKolor(kolor);
        }

        Samohud autko(marka, model, pojemnosc, paliwo, tmpKolor);
        samochody.push_back(autko);
    }

    return samochody;
}

void Plik::zapisz(std::vector<Samohud> samohody)
{
    if(this->otwarty){
        plik.close();
    }
    plik.open(nazwa, ios::out);
    if (plik.good()){
        for(auto samohud:samohody){
            plik <<samohud.getMarka()<<endl;
            plik <<samohud.getModel()<<endl;
            plik <<samohud.getPojemnosc()<<endl;
            plik <<samohud.getPaliwo()<<endl;
            plik <<samohud.getKolor().getKolor()<<endl;
        }
    }
}
