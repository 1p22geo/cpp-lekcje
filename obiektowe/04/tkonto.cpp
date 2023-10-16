#include "tkonto.h"
#include "string.h"
#include <iomanip>
#include <iostream>

TKonto::TKonto() : nazwa("BRAK_DANYCH") , numer(string(32, '0')),saldo(0){}
TKonto::TKonto(string n, string num, float sld):nazwa(n),numer(num),saldo(sld){
    if(saldo<0){
        saldo = 0;
    }
}

string TKonto::getNumer()
{
    return numer;
}

int TKonto::setNumer(string n)
{
    if(n.length() != 32){
        return -1;
    }

    numer = n;
    return 0;
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
    if(kwota>saldo){
        return -2;
    }
    this->saldo -= kwota;
    return 0;
}

int TKonto::przelew(TKonto *konto, float kwota)
{
    if(kwota<0){
        return -1;
    }
    if(kwota>saldo){
        return -2;
    }
    this->saldo -= kwota;
    konto->saldo += kwota;
    return 0;
}