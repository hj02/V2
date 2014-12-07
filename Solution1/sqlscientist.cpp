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
                  "VALUES(:name, :gender, :dateOfBirth, : dateOfDeath)");
    query.bindValue(":name", QString::fromStdString(s.name));
    query.bindValue(":gender", QString::fromStdString(s.gender));
    query.bindValue(":dateOfBirth",QString::fromStdString(s.dateOfBirth));
    query.bindValue(":dateOfDeath",QString::fromStdString(s.dateOfDeath));

    query.exec();



}
