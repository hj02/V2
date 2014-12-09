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

    QSqlQuery query;
    query.prepare("INSERT INTO Computer (Brand, Year, Type, Built)"
                  "VALUES(:Brand, :Year, :Type, :Built)");
    query.bindValue(":Brand", QString::fromStdString(c.brand));
    query.bindValue(":Year", QString::fromStdString(c.year));
    query.bindValue(":Type",QString::fromStdString(c.type));
    query.bindValue(":Built",QString::fromStdString(c.built));

    query.exec();
}


std::list<Computer> SqlComputer::searchComputer(std::string searchTerm){
    std::list<Computer> computer = std::list<Computer>();

    QSqlQuery query;
    searchTerm = "%" + searchTerm + "%";
    query.prepare("select * from Computer where Brand like :estr or Year like :estr or Type like :estr or Built like :estr");
    query.bindValue(":estr", QString::fromStdString(searchTerm));

    query.exec();

    Computer t = Computer();

        while(query.next()){
        t.brand = query.value("Brand").toString().toStdString();
        t.year = query.value("Year").toString().toStdString();
        t.type =query.value("Type").toString().toStdString();
        t.built = query.value("Built").toString().toStdString();
        computer.push_back(t);

        }

    return computer;

}


std::list<Computer> SqlComputer::list(std::string col, std::string mod){


    std::list<Computer> computer = std::list<Computer>();

    QSqlQuery query;

   if(col!="brand" && col!="year" && col!="type" && col!="built"){
       throw std::runtime_error(col + " is not a legal filter.");
    }
    if(mod!="desc" && mod!="asc") {

       throw std::runtime_error(mod + " is not a legal filter modifier.");
    }

   QString qstr ="SELECT * FROM Computer ORDER BY " + QString::fromStdString(col) + " " + QString::fromStdString(mod);
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

void SqlComputer::connect(std::string sID, std::string cID){



    QSqlQuery query;
    query.prepare("INSERT INTO Makers (c_ID, s_ID)"
                  "VALUES(:c_ID, :s_ID)");
    query.bindValue(":c_ID", QString::fromStdString(sID));
    query.bindValue(":s_ID", QString::fromStdString(cID));


    query.exec();



}
