#ifndef SQLCOMPUTER_H
#define SQLCOMPUTER_H
#include <computer.h>
#include <QtSql>

class SqlComputer
{
public:
    SqlComputer();
    std::list<Computer> list();
    std::list<Computer> list(std::string col, std::string mod);
    void addComputer(Computer c);
    Computer* search(std::string searchTerm);
    std::list<Computer> getComputerOrederedBy(std::string col, std::string mod);
};

#endif // SQLCOMPUTER_H
