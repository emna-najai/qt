#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "cage.h"
#include "qcustomplot.h"
#include "animal.h"
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSystemTrayIcon>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouterunecagebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_ajouter_cage_clicked()
{
    bool test;
    cage c (    ui->id_cage->text(),
                ui->nbr_max_cage->text().toInt(),
                ui->desc_cage->text()
                );

    test = c.ajouter();

    if (ui->id_cage->text().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez verifier le champs ID!!!!") ;

    }
    if(ui->nbr_max_cage->text().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez verifier le champs !!!!") ;
    }
    if (ui->nbr_max_cage->text().toInt()>10)
    {
        QMessageBox::information(this," ERREUR "," Le nombre maximal des animaux par cage ne peux pas exceder 10") ;

    }
    if (ui->desc_cage->text().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez ajouter une description") ;

    }

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter une cage "),
                          QObject::tr("La cage a eté ajoutée.\n"
                                      "Cliquez ok pour quitter."), QMessageBox::Ok);
        ui->afficher_cages->setModel(tmpc.afficher());



       QSqlQueryModel * model = new QSqlQueryModel;
       model->setQuery("select id from cage");
       ui->delid->setModel(model);
       ui->id_cageA->setModel(model);
       ui->delId_cageA->setModel(model);

    }
    else {
        QMessageBox::critical(0, qApp->tr("Ajout"),

                        qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



    }
    ui->id_cage->setText("");
    ui->desc_cage->setText("");
    ui->nbr_max_cage->setText("");
}




void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("select id from cage");
    ui->delid->setModel(model);
    ui->delId_cageA->setModel(model);
}


void MainWindow::on_supprimercage_clicked()
{
    QString id= ui->delid->currentText();
    bool test = tmpc.supprimer(id);
    if (test)
    {
        QString str = "Vous voulez vraiment supprimer \n la cage ayant pour reference : "+ ui->delid->currentText();
        int rep = QMessageBox::question(this, tr("cage"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch(rep) {
        case QMessageBox::Ok:
            if (tmpc.supprimer(id))
              {
                QMessageBox ::information(0, qApp->tr("Suppression"),
                                          qApp->tr("La cage a été supprimé"), QMessageBox::Ok);
                ui->afficher_cages->setModel(tmpc.afficher());
              }
            break;
        case QMessageBox::Cancel:

            break;
        default:
            break;
      }
        }

    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("select id from cage");
    ui->delid->setModel(model);
    ui->id_cageA->setModel(model);
    ui->delId_cageA->setModel(model);




}


void MainWindow::on_delid_activated(const QString &arg1)
{
    QString id= ui->delid->currentText();
    QSqlQuery qry;

    qry.prepare("select * from cage where id =:id");
    qry.bindValue(":id",id);
    qry.exec();
    while(qry.next()){
        ui->delnbr_animaux->setText(qry.value(1).toString());
        ui->deldesc->setText(qry.value(2).toString());

    }

}


void MainWindow::on_modifiercage_clicked()
{
    QString id = ui->delid->currentText();
    int nbrA = ui->delnbr_animaux->text().toInt();
    QString description = ui->deldesc->text();

    cage *c = new cage(id, nbrA, description);
    if(c->modifier(id))
    {
        QMessageBox::information(0, qApp->tr("Modification"),
            qApp->tr("Succès"), QMessageBox::Ok);
        ui->afficher_cages->setModel(tmpc.afficher());

    }
}


void MainWindow::on_pushButton_7_clicked() //ajouter un animal
{
    bool test;
    animal A(ui->refanimal->text(),
             ui->race->text(),
             ui->nom->text(),
             ui->sexe->currentText(),
             ui->id_cageA->currentText()
             );
    test = A.ajouter();
    if(ui->refanimal->text().isEmpty())
        {
            QMessageBox::information(this," ERREUR "," Veuillez verifier le champs ID!!!!") ;

        }
    if(ui->race->text().isEmpty())
        {
            QMessageBox::information(this," ERREUR "," Veuillez verifier le champs Race!!!!") ;

        }
    if(ui->sexe->currentText().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez verifier le champs sexe!!!!") ;

    }if(ui->nom->text().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez verifier le champs nom!!!!") ;

    }if(ui->id_cageA->currentText().isEmpty())
    {
        QMessageBox::information(this," ERREUR "," Veuillez verifier le champs ID!!!!") ;

    }

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter un Animal "),
                          QObject::tr("L'animal a été bien ajouté.\n"
                                      "Cliquez ok pour quitter."), QMessageBox::Ok);

        ui->listedesanimaux->setModel(tmpa.afficher());




       QSqlQueryModel * model = new QSqlQueryModel;
       model->setQuery("select id from animal");
       ui->delAnim->setModel(model);
    }
    else {
        QMessageBox::critical(0, qApp->tr("Ajout"),

                        qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    ui->refanimal->setText(""),
    ui->race->setText(""),
    ui->nom->setText("");

}
//animal::animal(QString id, QString race, QString nom, QString sexe, QString id_cage)


void MainWindow::on_ajouteranimalbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_homebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_delAnim_activated(const QString &arg1)
{
    QString id= ui->delAnim->currentText();
    QSqlQuery qry;
    qry.prepare("select * from animal where id=:id");
    qry.bindValue(":id",id);
    qry.exec();
    while (qry.next())
    {
        ui->delRace->setText(qry.value(1).toString());
        ui->delnom->setText(qry.value(2).toString());
      //ui->delsex->setCurrentIndex(qry.value(2).toString());
      //ui->delId_cageA->setCurrentIndex(qry.value(3).toString());
    }
}

void MainWindow::on_recherche_btn_clicked()
{
    //recherchecage

    QString rech=ui->recherchecage->text();
    if(rech!="")  { ui->afficher_cages->setModel(tmpc.recherche(rech)); }
qDebug()<<tmpc.recherche(rech);
}

void MainWindow::on_DelAnimal_clicked()
{
    QString id=ui->delAnim->currentText();
    bool test=tmpa.supprimer(id);
    if (test)
    {
        QString str="voulez vous vraiment supprimer \n l'animal ayant pour reference :"+ ui->delAnim->currentText();
        int rep = QMessageBox::question(this, tr("Animal"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch(rep) {
        case QMessageBox::Ok:
            if (tmpc.supprimer(id))
              {
                QMessageBox ::information(0, qApp->tr("Suppression"),
                                          qApp->tr("L'animal a été supprimé"), QMessageBox::Ok);
                ui->listedesanimaux->setModel(tmpa.afficher());
              }
            break;
        case QMessageBox::Cancel:

            break;
        default:
            break;
      }
        }
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("select id from animal");
    ui->delAnim->setModel(model);

    }




void MainWindow::on_ModifierAnimal_clicked()
{
    QString id= ui->delAnim->currentText();
    QString race = ui->delRace->text();
    QString nom = ui->delnom->text();
    QString sexe = ui->delsex->currentText();
    QString id_cage =ui->delId_cageA->currentText();

    animal *a = new animal(id, race, nom, sexe, id_cage);
    if(a->modifier(id))
    {
        QMessageBox::information(0, qApp->tr("Modification"),
            qApp->tr("Succès"), QMessageBox::Ok);
        ui->listedesanimaux->setModel(tmpa.afficher());
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_tri_desc_clicked()
{
    ui->listedesanimaux->setModel(tmpa.triNom());
}


void MainWindow::on_tri_desc_2_clicked()
{
    ui->listedesanimaux->setModel(tmpa.triSexe());
}

void MainWindow::on_tri_desc_3_clicked()
{
  ui->listedesanimaux->setModel(tmpa.triRace());
}



void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));

    ui->customPlot->setBackground(QBrush(gradient));


    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *nuclear = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    nuclear->setAntialiased(false);

    regen->setStackingGap(1);
    nuclear->setStackingGap(1);


    // set names and colors:
    nuclear->setName("Nombre");
    nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    nuclear->setBrush(QColor(250, 170, 20));
    regen->setName("Race");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));
    // stack bars on top of each other:

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    int i=0;
    QSqlQuery q;
    q.exec("select race from animal group by race");
    while(q.next())
    {
        QString race=q.value(0).toString();
        i++;
       // qDebug()<<"res :"<<race<<endl;

        ticks<<i;
        labels<<race;
    }


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 12.1);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:

    QVector<double> nuclearData;
    int j=0;
    QSqlQuery q2,q1;
    q2.exec("select count(id), race from animal group by race");
    q1.exec("select race from animal group by race");

    while(q2.next())
    {
       int nbr= q2.value(0).toInt();
     //  qDebug()<<"nombres :"<<nbr<<endl;

       j++;
       nuclearData<<nbr;

    }
    nuclear->setData(ticks, nuclearData);



    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}

class PrintBorder : public PagePrepare
{
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter)
{ // print a border on each page
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}

void MainWindow::uglyPrint2(QPrinter *printer) {

    // ---------------- death-to-designers example Event------------------

    QPainter uglyPainter;
    if(!uglyPainter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    TablePrinter uglyTablePrinter(&uglyPainter, printer);
    QVector<int> colStretch = QVector<int>() << 2 << 5 << 10;
    uglyTablePrinter.setPen(QPen(QColor(0, 100, 255), 3, Qt::DotLine)); // pen for borders
    uglyTablePrinter.setHeaderColor(Qt::black);
    uglyTablePrinter.setContentColor(Qt::magenta);
    QFont font1; // font for headers
    font1.setBold(true);
    QFont font2; // font for content
    font2.setItalic(true);
    uglyTablePrinter.setHeadersFont(font1);
    uglyTablePrinter.setContentFont(font2);
    PrintBorder *printB = new PrintBorder;
    printB->pageNumber = 1;
    uglyTablePrinter.setPagePrepare(printB);
    QVector<QString> headers = QVector<QString>() << "id" << "nbr_animaux" << "description" ;

    uglyPainter.setPen(QPen(Qt::red));
    uglyPainter.drawText(uglyPainter.viewport().width()/2 - 40, 40, "VOS CAGES");
    uglyPainter.translate(0, 60); // start print point
    uglyTablePrinter.setCellMargin(10, 5, 5, 5);
    uglyTablePrinter.setPageMargin(100, 40, 40, 40);
    if(!uglyTablePrinter.printTable(ui->afficher_cages->model(), colStretch, headers)) {
        qDebug() << uglyTablePrinter.lastError();
    }
    uglyPainter.end();
    delete printB;
}

void MainWindow::on_print_clicked()
{
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(uglyPrint2(QPrinter*)));
    dialog.exec();
}

