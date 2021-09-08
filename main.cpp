#include "mainwindow.h"
#include "connection.h"
#include "QMessageBox"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    w.show();

    bool test=c.createConnect();
    QMessageBox::information(nullptr, QObject::tr("a"),
                             QObject::tr("test.\n"
                                         "Click ok to start."), QMessageBox::Ok);


    if(test)
    {

    w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click ok to start."), QMessageBox::Ok);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
    }
