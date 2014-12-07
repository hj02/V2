#include "computer.h"

Computer::Computer()
{
    brand = "";
    year = "";
    type = "";
    built = "";
}

bool Computer::operator==(const Computer& right) {
    return this->brand == right.brand;
}
