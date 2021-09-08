#ifndef ANIMAL_H
#define ANIMAL_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>


class animal
{
public:
    animal();
    animal(QString id, QString race, QString nom, QString sexe, QString id_cage);
    QString getId();
    QString getRace();
    QString getNom();
    QString getSexe();
    QString getIdcage();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString);
    bool modifier(QString);

    QSqlQueryModel *triRace();
    QSqlQueryModel *triNom();
    QSqlQueryModel *triSexe();


private :
    QString id, race,nom, sexe,id_cage;
};

#endif // ANIMAL_H
