#pragma once
#include <cmath>
#include "lib.h"

class Rownanie{
    public:
        polaRownania pola;
        Rownanie(polaRownania _pola);
        wynik policz();
        std::string to_string();
};