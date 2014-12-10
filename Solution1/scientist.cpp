#include "scientist.h"

Scientist::Scientist() {

    sID = 0;
    name = "";
    dateOfBirth = "";
    dateOfDeath = "";
    gender = "";
    brand ="";

}

bool Scientist::operator==(const Scientist& right) {
    return this->name == right.name;
}
