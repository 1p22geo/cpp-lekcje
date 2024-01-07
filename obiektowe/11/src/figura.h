#pragma once
#include <string>

class Figura{
    protected:
        float pole;
        float obwod;
    public:
        virtual void obliczPole() = 0;
        virtual void obliczObwod() = 0;
        Figura();
        virtual std::string info() = 0;
        friend void znajdz_w_tabeli_figure_o_najwiekszej_powierzchni_i_wypisz_informacje_o_niej_na_ekranie(Figura** tab, int len);
};