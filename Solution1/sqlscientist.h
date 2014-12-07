#ifndef SQLSCIENTIST_H
#define SQLSCIENTIST_H
#include <scientist.h>
#include <QtSql>


class SqlScientist
{
public:
    SqlScientist();
    std::list<Scientist> list();
    void addScientist(Scientist s);

};

#endif // SQLSCIENTIST_H
