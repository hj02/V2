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
    std::list<Scientist> searchScientist(std::string searchTerm, std::string ShowComp);
    void openDatabase();
};
#endif // SQLSCIENTIST_H


