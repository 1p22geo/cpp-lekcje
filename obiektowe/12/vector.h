#include <string>

class Vector{
    public:
        Vector();
        Vector(float x, float y);
        float getX();
        float getY();
        std::string to_string();

        Vector operator +(Vector that);
        Vector operator -(Vector that);
    protected:
        float x;
        float y;
};