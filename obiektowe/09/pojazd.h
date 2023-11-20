#pragma once
#include <string>


class Pojazd{
    protected:
        std::string nazwa;
        int rocznik;
    public:
        Pojazd();
        Pojazd(std::string _nazwa, int _rocznik);
        std::string getNazwa();
        int getRocznik();
};