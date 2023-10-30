#include "osoba.h"
#include "pilkarz.h"
#include "student.h"
#include "pilkarze/nozny.h"
#include "pilkarze/reczny.h"
#include <iostream>

int main(){

    Osoba *os = new Osoba("Bartosz", "Ge.", "28.10.2009");
    cout<<"Utworzono osobe: "<<endl;
    os->WypiszInfo();

    PilkarzNozny *nz = new PilkarzNozny("Robert", "El", "nie wiem w sumie", "napastnik chyba", "legia? nie wiem jakis tam");
    PilkarzReczny *rc = new PilkarzReczny("Stanislaw", "Q", "29.02.2016", "libero? nie wiem jakie tam sa pozycje", "eeeeee... yyyyyyyy... PAPRYKA");
    nz->StrzelGola();
    nz->StrzelGola();
    rc->StrzelGola();
    nz->StrzelGola();
    rc->StrzelGola();
    nz->WypiszInfo();
    rc->WypiszInfo();

    return 0;
}