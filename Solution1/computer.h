#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>
#include <ctime>


class Computer
{
public:
    Computer();

    bool operator==(const Computer& right);
    std::string brand;
    std::string year;
    std::string type;
    std::string built;
};

#endif // COMPUTER_H

