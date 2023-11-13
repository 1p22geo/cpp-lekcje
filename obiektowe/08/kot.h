#include "zwierze.h"

class Kot : public Zwierze {
    protected:
        int lata;
    public:
        Kot();
        Kot(int _lata, string _nazwa);
        void przedstawSie();

};