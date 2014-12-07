#ifndef COMPUTER_H
#define COMPUTER_H

#include <ctime>
#include <string>


class Computer
{
public:
    Computer();
    bool operator==(const Scientist &rhs);
    std::string brand;
    std::string year;
    std::string type;
    std::string built;
};

#endif // COMPUTER_H
