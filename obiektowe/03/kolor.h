#include <iostream>
using namespace std;

class Kolor{
    private:
        string nazwa;
        int R,G,B;
        bool hex;
    public:
        Kolor(string nazwa);
        Kolor();
        Kolor(int r, int g, int b);
        string getKolor();
        // void setKolor(int r, int g, int b);
        // void setKolor(string nazwa);
        // bool isRGB();
};