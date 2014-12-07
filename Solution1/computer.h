#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>

#include <ctime>
#include <string>


#include <ctime>
#include <string>


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

