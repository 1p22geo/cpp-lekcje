#include "errors.h"

DeltaUjemnaError::DeltaUjemnaError(Rownanie *_r):rownanie(_r){}

std::string DeltaUjemnaError::to_string()
{
    std::stringstream ss;
    ss<<"W rownaniu "<<rownanie->to_string()<<" delta wychodzi ujemna"<<std::endl;
    return std::string(ss.str());
}

Error::Error(RownanieError *__er):_er(__er){}

RownanieLinioweError::RownanieLinioweError(Rownanie *_r, float _x):rownanie(_r), x(_x){}

std::string RownanieLinioweError::to_string()
{
    std::stringstream ss;
    ss<<"Rownanie "<<rownanie->to_string()<<" jest tak naprawde liniowe a jego rozwiozanie to "<<x<<std::endl;
    return std::string(ss.str());
}

RownanieSprzeczneLiniowe::RownanieSprzeczneLiniowe(Rownanie *_r):rownanie(_r){}

std::string RownanieSprzeczneLiniowe::to_string()
{
std::stringstream ss;
    ss<<"Rownanie "<<rownanie->to_string()<<" jest liniowe I sprzeczne"<<std::endl;
    return std::string(ss.str());
}
