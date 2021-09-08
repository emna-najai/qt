#include "cage.h"

cage::cage()
{
    id="";
    nbr_animaux=0;
    description="";

}
cage::cage(int nbr_animaux, QString description)
{
    this->nbr_animaux=nbr_animaux;
    this->description=description;
}

cage::cage(QString id, int nbr_animaux, QString description)
{
    this->id=id;
    this->nbr_animaux=nbr_animaux;
    this->description=description;
}


QString cage::getId() { return id; };
int cage::getNbranimaux() {return nbr_animaux;}
QString cage::getDescription() {return description; }

bool cage::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CAGE (id, nbr_animaux, description)"
                  "VALUES (:id,:nbr_animaux,:description)");
    query.bindValue(":id",id);
    query.bindValue(":nbr_animaux",nbr_animaux);
    query.bindValue(":description",description);

    return query.exec();

}
QSqlQueryModel * cage::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from cage");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_animaux"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr(("description")));

    return model;

}

bool cage::supprimer(QString id)
{
   QSqlQuery query;
   query.prepare("Delete from CAGE where id = :id");
   query.bindValue(":id",id);
   return query.exec();
}

bool cage::modifier(QString id)
{
    QSqlQuery query;

    query.prepare("update cage SET id=:id, nbr_animaux=:nbr_animaux, description=:description WHERE id=:id");
    query.bindValue(":id",id);
    query.bindValue(":nbr_animaux",nbr_animaux);
    query.bindValue(":description",description);

    return query.exec();
}
QSqlQueryModel * cage::recherche(const QString &rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();

model->setQuery("select * from CAGE where (id LIKE '"+rech+"%' OR nbr_animaux LIKE '"+rech+"%' OR description LIKE '"+rech+"%') ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_animaux"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr(("description")));

    return model;

}


