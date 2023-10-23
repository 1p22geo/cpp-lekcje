#pragma once
#include "baseA.h"
#include <iostream>
using namespace std;


class ChildA : public BaseA{
    public:
        ChildA(string pbA, string cA, string prA);
        ChildA();
        string chA;
        string getPrtA();
        string info();
};