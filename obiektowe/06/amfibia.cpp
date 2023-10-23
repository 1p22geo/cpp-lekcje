#include "amfibia.h"
#include "auto.h"
#include "boat.h"
#include <iostream>
#include <sstream>


Amphibian::Amphibian()
{
    this->wheels = 4;
    this->swimming = false;
    this->isAmphibian = true;
}

Amphibian::Amphibian(bool sw, int wh, bool is)
{
    this->wheels = wh;
    this->swimming = sw;
    this->isAmphibian = is;
}

bool Amphibian::getIsAmphibian()
{
    return isAmphibian;
}

std::string Amphibian::info()
{
    if(isAmphibian){
        return "An amphibian which IS an amphibian, which is \n"+Car::info()+"\n\tAND\n"+Boat::info();
    }
    else{
        return "An amphibian which ISN'T an amphibian, which is \n"+Car::info()+"\n\tAND\n"+Boat::info();
    }
}
