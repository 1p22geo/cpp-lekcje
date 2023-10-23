#include "auto.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Car::Car():wheels(4)
{
}

Car::Car(int wh) :wheels(wh)
{
}

std::string Car::info()
{
    std::stringstream stream;

    stream << "A car with "<<wheels<<" wheels";
    
    std::string result(stream.str());
    return result;
}
