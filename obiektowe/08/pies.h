#include "zwierze.h"

class Pies : public  Zwierze {
    protected:
        int rok_ur;
    public:
        Pies();
        Pies(int _rok_ur, string _nazwa);
        void przedstawSie();
};