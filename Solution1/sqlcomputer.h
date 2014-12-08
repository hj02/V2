#ifndef SQLCOMPUTER_H
#define SQLCOMPUTER_H
#include <computer.h>
#include <QtSql>
#include <stdexcept>

class SqlComputer
{
public:
    SqlComputer();
    std::list<Computer> list();
    std::list<Computer> list(std::string col, std::string mod);
    void addComputer(Computer c);
    Computer* search(std::string searchTerm);

};

#endif // SQLCOMPUTER_H
