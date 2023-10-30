#include "nozny.h"

PilkarzNozny::PilkarzNozny(string imie_, string nazwizko_, string dataUrodzenia_, string pozycja_, string klub_): Pilkarz(imie_, nazwizko_, dataUrodzenia_, pozycja_, klub_)
{
}

void PilkarzNozny::StrzelGola()
{
    Pilkarz::StrzelGola();
    cout<<"Nozny szczelil gola!"<<endl;
}
