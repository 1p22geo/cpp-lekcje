#pragma once
#include <iostream>

class Car{
    protected:
        int wheels;
    public:
        Car();
        Car(int wh);
        std::string info();
        int getWheels;
};