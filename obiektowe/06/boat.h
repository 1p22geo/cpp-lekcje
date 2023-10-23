#pragma once
#include <iostream>

class Boat{
    protected:
        bool swimming;
    public:
        Boat();
        Boat(bool sw);
        void setSwimming(bool sw);
        bool getSwimming();
        std::string info();
};