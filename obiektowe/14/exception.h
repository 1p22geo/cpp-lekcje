#pragma once
#include <iostream>
#include <string>
#include <sstream>


class TrojkotWyjotek{
    public:
        TrojkotWyjotek(int a, int b, int c);
        int bokA;
        int bokB;
        int bokC;
        std::string to_string();
};