#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>

class Computer
{
public:
    Computer();
    bool operator==(const Computer& right);
    int cID;
    std::string brand;
    std::string year;
    std::string type;
    std::string built;
    std::string name;
};
#endif // COMPUTER_H

