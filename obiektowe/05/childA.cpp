#include "childA.h"

ChildA::ChildA(string pbA, string cA, string prA): chA(cA)
{
    this->pubA = pbA;
    this->prtA = prA;
}

ChildA::ChildA()
{
}

string ChildA::getPrtA()
{
    return this->prtA;
}

string ChildA::info()
{
    return BaseA::info()+\
    "ChildA ->\nprivA: "+this->pubA+"\nprtA: "+this->prtA+"\nchA: "+this->chA+"\n\n";
}
