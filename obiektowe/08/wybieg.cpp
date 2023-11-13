#include "wybieg.h"

Wybieg::Wybieg()
{
    maxIlosc = 1;
    ilosc = 0;
    wybieg = new Zwierze();
}

Wybieg::Wybieg(int _maxIlosc)
{
    maxIlosc = _maxIlosc;
    ilosc = 0;
    wybieg = new Zwierze();

}
