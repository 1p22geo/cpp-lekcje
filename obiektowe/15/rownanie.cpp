#include "rownanie.h"
#include "errors.h"

Rownanie::Rownanie(polaRownania _pola)
{
    this->pola = _pola;
}

wynik Rownanie::policz()
{
    wynik w;

    float delta = std::pow(pola.b, 2) - (4*pola.a*pola.c);

    if(delta<0){
        throw new Error( new DeltaUjemnaError(this));
    }

    if(pola.a == 0){
        if(pola.b == 0){
            throw new Error( new RownanieSprzeczneLiniowe(this));
        }
        throw new Error( new RownanieLinioweError(this, (-pola.c)/pola.b));
    }

    w.x1 = (-pola.b + std::sqrt(delta) )/2*pola.a;
    w.x2 = (-pola.b - std::sqrt(delta) )/2*pola.a;

    return w;
}

std::string Rownanie::to_string()
{
    std::stringstream ss;
    ss<<pola.a<<" x^2 + "<<pola.b<<" x + "<<pola.c<<" = 0";
    return std::string(ss.str());
}
