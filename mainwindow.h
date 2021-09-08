#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cage.h"
#include "animal.h"
#include "TablePrinter.h"
#include <QSoundEffect>
#include <QSound>
#include <QMediaPlayer>
#include <QPrinter>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    cage tmpc;
    animal tmpa;

private slots:
    void on_Ajouterunecagebtn_clicked();

    void on_ajouter_cage_clicked();

   // void on_modifier_cage_clicked();

  //  void on_supprimer_cage_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_supprimercage_clicked();

    void on_delid_activated(const QString &arg1);

    void on_modifiercage_clicked();

    void on_pushButton_7_clicked();

    void on_ajouteranimalbtn_clicked();

    void on_tri_desc_2_clicked();

    void on_homebtn_clicked();

    void on_pushButton_6_clicked();

    void on_delAnim_activated(const QString &arg1);

    void on_DelAnimal_clicked();

    void on_ModifierAnimal_clicked();

    void on_tri_desc_clicked();

    void on_tri_desc_3_clicked();

    void on_pushButton_10_clicked();

    void on_recherche_btn_clicked();

    void on_print_clicked();

    void uglyPrint2(QPrinter *printer);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
