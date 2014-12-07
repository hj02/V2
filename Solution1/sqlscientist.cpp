#include "sqlscientist.h"
#include <QtSql>
using namespace std;


SqlScientist::SqlScientist()
{
    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();
}



