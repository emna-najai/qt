#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSound>
#include <QMediaPlayer>
#include "qcustomplot.h"
#include <QSoundEffect>
#include <qsystemtrayicon.h>



class Connection
{
public:
    Connection();
    bool createConnect();
};

#endif // CONNECTION_H
