#include "computer.h"

Computer::Computer(){
    cID=0;
    brand = "";
    year = "";
    type = "";
    built = "";
    name = "";

}

bool Computer::operator==(const Computer& right) {
    return this->brand == right.brand;
}
