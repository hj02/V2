#ifndef SQLSCIENTIST_H
#define SQLSCIENTIST_H
#include <scientist.h>
#include <QtSql>
#include <stdexcept>

class SqlScientist
{
public:
    SqlScientist();
    std::list<Scientist> list();
    std::list<Scientist> list(std::string col, std::string mod);
    void addScientist(Scientist s);
    Scientist* search(std::string searchTerm);

};

#endif // SQLSCIENTIST_H


