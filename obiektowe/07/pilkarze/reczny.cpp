#include "reczny.h"

PilkarzReczny::PilkarzReczny(string imie_, string nazwizko_, string dataUrodzenia_, string pozycja_, string klub_): Pilkarz(imie_, nazwizko_, dataUrodzenia_, pozycja_, klub_)
{
}

void PilkarzReczny::StrzelGola()
{
    Pilkarz::StrzelGola();
    cout<<"Reczny szczelil gola!"<<endl;
}
