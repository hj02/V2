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
    Computer* searchComputer(std::string searchTerm);
    void openDatabase();

};

#endif // SQLCOMPUTER_H
