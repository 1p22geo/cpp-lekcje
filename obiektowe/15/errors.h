#pragma once
#include "lib.h"
#include "rownanie.h"



class RownanieError: public std::exception{
    public:
        virtual std::string to_string() = 0;
};

class DeltaUjemnaError: public RownanieError{
    private:
        Rownanie *rownanie;
    public:
        DeltaUjemnaError(Rownanie *_r);
        std::string to_string();
};

class RownanieSprzeczneLiniowe: public RownanieError{
    private:
        Rownanie *rownanie;
    public:
        RownanieSprzeczneLiniowe(Rownanie *_r);
        std::string to_string();
};


class RownanieLinioweError: public RownanieError{
    private:
        Rownanie *rownanie;
        float x;
    public:
        RownanieLinioweError(Rownanie *_r, float _x);
        std::string to_string();
};


class Error: public std::exception{
    public:
        RownanieError *_er;
        Error(RownanieError *__er);
};