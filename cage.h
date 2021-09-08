#ifndef CAGE_H
#define CAGE_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>


class cage
{
public:
    cage();
    cage (int nbr_animaix,QString description);
    cage(QString id, int nbr_animaux, QString description);

    QString getId();
    int getNbranimaux();
    QString getDescription();

    bool ajouter();
    QSqlQueryModel  * afficher();
    bool supprimer(QString);
    bool modifier(QString);

    QSqlQueryModel *recherche(const QString &rech);
    QSqlQuery *tri();


private:
    QString id;
    int nbr_animaux;
    QString description;
};

#endif // CAGE_H
