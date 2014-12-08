#include "sqlcomputer.h"
#include "sqlscientist.h"
#include "computer.h"
#include <QtSql>
using namespace std;

SqlComputer::SqlComputer()
{
}

std::list<Computer> SqlComputer::list(){

    std::list<Computer> computer = std::list<Computer>();

    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();

    QSqlQuery query;
    query.exec("SELECT * FROM Computer");

    while(query.next()){
        Computer c = Computer();
        c.brand = query.value("Brand").toString().toStdString();
        c.year = query.value("Year").toString().toStdString();
        c.type =query.value("Type").toString().toStdString();
        c.built = query.value("Built").toString().toStdString();

        computer.push_back(c);

    }

    return computer;

}

void SqlComputer::addComputer(Computer c){

    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO Computer (Brand, Year, Type, Built)"
                  "VALUES(:Brand, :Year, :Type, :Built)");
    query.bindValue(":Brand", QString::fromStdString(c.brand));
    query.bindValue(":Year", QString::fromStdString(c.year));
    query.bindValue(":Type",QString::fromStdString(c.type));
    query.bindValue(":Built",QString::fromStdString(c.built));

    query.exec();
}


Computer* SqlComputer::search(std::string searchTerm){

Computer* t;
return t;
}


std::list<Computer> SqlComputer::list(std::string col, std::string mod){


    std::list<Computer> computer = std::list<Computer>();

    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();


    QSqlQuery query;

   if(col!="brand" && col!="year" && col!="type" && col!="built"){
       throw std::runtime_error(col + " is not a legal filter.");
    }
    if(mod!="desc" && mod!="asc") {

       throw std::runtime_error(mod + " is not a legal filter modifier.");
    }

   QString qstr ="SELECT * FROM Scientist ORDER BY " + QString::fromStdString(col) + " " + QString::fromStdString(mod);
   query.exec(qstr);


    while(query.next()){
        Computer c = Computer();
        c.brand = query.value("Brand").toString().toStdString();
        c.year = query.value("Year").toString().toStdString();
        c.type =query.value("Type").toString().toStdString();
        c.built = query.value("Built").toString().toStdString();

        computer.push_back(c);

    }
    return computer;
}
