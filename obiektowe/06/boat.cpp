#include "boat.h"
#include <iostream>
#include <string>
#include <sstream>

Boat::Boat():swimming(false)
{
    
}

Boat::Boat(bool sw):swimming(sw)
{
}

void Boat::setSwimming(bool sw)
{
    this->swimming = sw;
}

bool Boat::getSwimming()
{
    return this->swimming;
}

std::string Boat::info()
{
    std::stringstream stream;

    stream << "A boat that ";

    if(swimming){
        stream<<"can swim";
    }
    else{
        stream <<"can't swim";
    }
    stream <<std::endl;
    
    std::string result(stream.str());
    return result;
}
