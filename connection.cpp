#include "connection.h"

Connection::Connection()
{

}
bool Connection::createConnect()
{
    bool test=false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ProjetQt");
    db.setUserName("Emna");
    db.setPassword("Emna21");

    if(db.open())

         test=true;

    return test;

}
