#ifndef SQLSCIENTIST_H
#define SQLSCIENTIST_H
#include <scientist.h>
#include <QtSql>


class SqlScientist
{
public:
    SqlScientist();
    std::list<Scientist> list();
    std::list<Scientist> list(std::string col, std::string mod);
    void addScientist(Scientist s);
    Scientist* search(std::string searchTerm);
    std::list<Scientist> getScientistOrederedBy(std::string col, std::string mod);

};

#endif // SQLSCIENTIST_H


