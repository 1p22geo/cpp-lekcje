#include "pilkarz.h"

Pilkarz::Pilkarz(string imie_, string nazwizko_, string dataUrodzenia_, string pozycja_, string klub_) : Osoba(imie_, nazwizko_, dataUrodzenia_)
{  
    this->pozycja = pozycja_;
    this->klub = klub_;
}

void Pilkarz::WypiszInfo()
{
    cout << "\tPilkarz:"<<endl;
    Osoba::WypiszInfo();
    cout<<"pozycja: "<<this->pozycja<<endl;
    cout<<"klub: "<<this->klub<<endl;
    cout<<"goli szczelil: "<<this->liczbaGoli<<endl;
}

void Pilkarz::StrzelGola()
{
    this->liczbaGoli += 1;
}
