#include <iostream>
using namespace std;

class Kolor{
    private:
        string nazwa;
        bool hex;
        int R,G,B;
    public:
        void setKolor(int r, int g, int b);
        void setKolor(string n);
        Kolor(string nazwa);
        Kolor();
        Kolor(int r, int g, int b);
        string getKolor();
        // void setKolor(int r, int g, int b);
        // void setKolor(string nazwa);
        // bool isRGB();
};