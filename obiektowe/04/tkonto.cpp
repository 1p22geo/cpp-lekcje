#include "tkonto.h"
#include "string.h"
#include <iomanip>
#include <iostream>

TKonto::TKonto() : nazwa("BRAK_DANYCH") , numer(string(32, '0')),saldo(0){}
TKonto::TKonto(string n, string num, float sld):nazwa(n),numer(num),saldo(sld){}

string TKonto::getNumer()
{
    return numer;
}

void TKonto::setNumer(string n)
{
    numer = n;
}

string TKonto::toString()
{
    std::stringstream stream;

    stream << "Depozytariusz: "<<nazwa<<endl
    << "Numer konta: "<<numer<<endl
    << "Saldo: "<<saldo <<endl
    
    <<endl;
    std::string result(stream.str());
    return result;

}

int TKonto::wplata(float kwota)
{
    if(kwota<0){
        return -1;
    }
    this->saldo += kwota;
    return 0;
}

int TKonto::wyplata(float kwota)
{
    if(kwota<0){
        return -1;
    }
    this->saldo -= kwota;
    return 0;
}
