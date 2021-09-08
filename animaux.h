#ifndef ANIMAUX_H
#define ANIMAUX_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Animaux
{
    QString id;
    QString race;
    QString sexe;
    QString nom;
    QString id_cage;

public:
     Animaux();
     Animaux(QString id, QString race, QString sexe, QString nom,QString id_cage);
    //Animal(QString race, QString sexe, QString nom,QString id_cage);
    QString getId();
    QString getRace();
    QString getNom();
    QString getSexe();
    QString getIdCage();

    bool ajouter_animal();
    QSqlQueryModel *Afficher();
    bool supprimer(QString);
    QSqlQueryModel(QString);
    bool modifier();
    QSqlQueryModel* triparRace();
    QSqlQueryModel* triparSexe();
    QSqlQueryModel* triparIdCage();

};

#endif // ANIMAUX_H
