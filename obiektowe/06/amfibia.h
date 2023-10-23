#pragma once
#include "auto.h"
#include "boat.h"
#include <iostream>

class Amphibian : public Boat, public Car{
    private:
        bool isAmphibian;
    public:
        Amphibian();
        Amphibian(bool sw, int wh, bool is);
        bool getIsAmphibian();
        std::string info();

};