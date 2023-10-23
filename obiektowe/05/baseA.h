#pragma once
#include <iostream>

using namespace std;


class BaseA{
    private:
        string privA = "default";
    public:
        string pubA = "default";
        string info();
    protected:
        string prtA = "default";

};