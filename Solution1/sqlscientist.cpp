#include "sqlscientist.h"
#include <QtSql>
using namespace std;


SqlScientist::SqlScientist()
{

}

std::list<Scientist> SqlScientist::list(){

    std::list<Scientist> scientist = std::list<Scientist>();

    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();

    QSqlQuery query;
    query.exec("SELECT * FROM Scientist");

    while(query.next()){
        Scientist s = Scientist();
        s.name = query.value("Name").toString().toStdString();
        s.gender = query.value("Gender").toString().toStdString();
        s.dateOfBirth =query.value("Dob").toString().toStdString();
        s.dateOfDeath = query.value("Dod").toString().toStdString();

        scientist.push_back(s);

    }

    return scientist;

}

void SqlScientist::addScientist(Scientist s){

    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO Scientist (Name, Gender, Dob, Dod)"
                  "VALUES(:Name, :Gender, :Dob, :Dod)");
    query.bindValue(":Name", QString::fromStdString(s.name));
    query.bindValue(":Gender", QString::fromStdString(s.gender));
    query.bindValue(":Dob",QString::fromStdString(s.dateOfBirth));
    query.bindValue(":Dod",QString::fromStdString(s.dateOfDeath));

    query.exec();



}

Scientist* SqlScientist::search(std::string searchTerm){

Scientist* t;
return t;
}

std::list<Scientist> SqlScientist::getScientistOrederedBy(std::string col, std::string mod){

std::list<Scientist> scientist = std::list<Scientist>();

return scientist;
}

std::list<Scientist> SqlScientist::list(std::string col, std::string mod){

std::list<Scientist> scientist = std::list<Scientist>();

return scientist;
}
