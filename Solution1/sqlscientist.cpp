#include "sqlsicentist.h"
#include "scientistrepository.h"
#include <QtSql>
using namespace std;


SqlSicentist::SqlSicentist()
{
    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("V2.sqlite");
    db.open();
}



