#include "animal.h"

animal::animal()
{
    id="";
    race ="";
    nom ="";
    sexe="";
    id_cage="";
}
animal::animal(QString id, QString race, QString nom, QString sexe, QString id_cage)
{
    this->id=id;
    this->race=race;
    this->nom=nom;
    this->sexe=sexe;
    this->id_cage=id_cage;
}

QString animal::getId() {return id;}
QString animal::getIdcage(){return id_cage;}
QString animal::getNom() {return nom;}
QString animal::getRace() {return race;}
QString animal::getSexe() {return sexe;}

bool animal::ajouter()
{
    QSqlQuery qry;
    qry.prepare("insert into animal (id, race, nom, sexe, id_cage)"
                "VALUES(:id,:race,:nom,:sexe,:id_cage)");
    qry.bindValue(":id",id);
    qry.bindValue(":race",race);
    qry.bindValue(":nom",nom);
    qry.bindValue(":sexe",sexe);
    qry.bindValue(":id_cage",id_cage);
    return qry.exec();
}

QSqlQueryModel * animal::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from animal");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_cage"));

return model;

}

bool animal::supprimer(QString id)
{
    QSqlQuery qry;
    qry.prepare("delete from animal where id=:id");
    qry.bindValue(":id",id);
    return qry.exec();
}

bool animal::modifier(QString id)
{
    QSqlQuery query;
    query.prepare("update animal SET id=:id, race=:race, nom=:nom, sexe=:sexe, id_cage=:id_cage where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":race",race);
    query.bindValue(":nom",nom);
    query.bindValue(":sexe",sexe);
    query.bindValue(":id_cage",id_cage);

    return query.exec();

}
QSqlQueryModel* animal::triNom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from animal ORDER BY nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_cage"));



    return model;
}

QSqlQueryModel* animal::triRace()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from animal ORDER BY RACE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_cage"));

    return model;
}


QSqlQueryModel * animal::triSexe()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select * from animal order BY sexe");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_cage"));
    return model;
}




