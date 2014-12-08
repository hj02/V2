#include "sqlscientist.h"
#include <QtSql>
using namespace std;


SqlScientist::SqlScientist()
{

}

std::list<Scientist> SqlScientist::list(){

    std::list<Scientist> scientist = std::list<Scientist>();

    openDatabase();

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

    openDatabase();

    QSqlQuery query;
    query.prepare("INSERT INTO Scientist (Name, Gender, Dob, Dod)"
                  "VALUES(:Name, :Gender, :Dob, :Dod)");
    query.bindValue(":Name", QString::fromStdString(s.name));
    query.bindValue(":Gender", QString::fromStdString(s.gender));
    query.bindValue(":Dob",QString::fromStdString(s.dateOfBirth));
    query.bindValue(":Dod",QString::fromStdString(s.dateOfDeath));

    query.exec();



}

std::list<Scientist> SqlScientist::searchScientist(std::string searchTerm){
    std::list<Scientist> scientist = std::list<Scientist>();
    openDatabase();

    QSqlQuery query;
    searchTerm = "%" + searchTerm + "%";
    query.prepare("select * from Scientist where Name like :estr or Gender like :estr or Dob like :estr or Dod like :estr");
    query.bindValue(":estr", QString::fromStdString(searchTerm));

    query.exec();

    Scientist t = Scientist();

        while(query.next()){
        t.name = query.value("Name").toString().toStdString();
        t.gender = query.value("Gender").toString().toStdString();
        t.dateOfBirth =query.value("Dob").toString().toStdString();
        t.dateOfDeath = query.value("Dod").toString().toStdString();
        scientist.push_back(t);

        }

    return scientist;

}

std::list<Scientist> SqlScientist::list(std::string col, std::string mod){

    std::list<Scientist> scientist = std::list<Scientist>();

    openDatabase();

    QSqlQuery query;

   if(col!="name" && col!="gender" && col!="dob" && col!="dod"){
       throw std::runtime_error(col + " is not a legal filter.");
    }
    if(mod!="desc" && mod!="asc") {

       throw std::runtime_error(mod + " is not a legal filter modifier.");
    }

   QString qstr ="SELECT * FROM Scientist ORDER BY " + QString::fromStdString(col) + " " + QString::fromStdString(mod);
   query.exec(qstr);


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

void SqlScientist::openDatabase(){


    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();

}
