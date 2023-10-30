#include "student.h"

Student::Student(string imie_, string nazwizko_, string dataUrodzenia_, int rok_, int grupa_, int nrIndeksu_) :Osoba(imie_, nazwizko_, dataUrodzenia_)
{
    this->rok = rok_;
    this->grupa = grupa_;
    this->nrIndeksu = nrIndeksu_;
}

void Student::WypiszInfo()
{
    cout << "\tStudent:"<<endl;
    Osoba::WypiszInfo();
    cout<<"rok: "<<this->rok<<endl;
    cout<<"grupa: "<<this->grupa<<endl;
    cout<<"nr indeksu: "<<this->nrIndeksu<<endl;
}
