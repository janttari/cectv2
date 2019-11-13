#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QFileInfo>

QList<QString>skripti; //tähän listaan mikä skripti kanvaa valittaessa suoritetaan. luetaan kanavien konffista
QProcess prosessi; //suoritettava skripti tässä prosessissa
QString pidFile = "/tmp/cectv2_playerpid"; //suoritettavan soitin-skriptin pid kirjoitetaan tähän tiedostoon
QString commandFile="/dev/shm/cectv2"; //Tähän tiedostoon kirjoittamalla voi lähettää tälle ohjelmalle komentoja
QString projektiHakemisto = "/opt/cectv2"; //voidaan ohittaa antamalla argumenttina hakemisto ohjelmalle komentoriviltä

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);                           //Luodaan uusi timer
    connect(timer, SIGNAL(timeout()), this, SLOT(kello()));
    timer->start(100);

    tausta.show(); //taustalomake, joka näytetään kun streamia ollaan avaamassa
    QMainWindow::move(QPoint(0,0)); //siirretään ikkuna vasempaan yläkulmaan
    QMainWindow::setWindowFlags(Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    QDesktopWidget* widget = qApp->desktop(); //etsitään näytön koko
    QRect screenSize = widget->availableGeometry(widget->primaryScreen());
    int xkoko = screenSize.width();
    int ykoko = screenSize.height();
    QMainWindow::setFixedWidth(xkoko); //laitetaan koko näytön levyiseksi
    QMainWindow::setFixedHeight(ykoko); //laitetaan korkeus xx pikseliä
    ui->label->setFixedWidth(xkoko);
    ui->listWidget->setFocus();
    ui->listWidget->move(40,30);
    ui->listWidget->setFixedHeight(ykoko);
    ui->listWidget->setFixedWidth(xkoko);
    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200,120)); //ikonit on 400x240 png, näytetään ne puolet pienempinä
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    haeKonffi();
    ui->listWidget->setCurrentRow(0); //asetetaan focus ekaan kohteeseen
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::kello() //Tässä valvotaan komentotiedostoa, päivitetään kellonaikaa labeliin ja valvotaan, jos prosessi (omxplayer tms) on loppunut
{
    if(QFileInfo(commandFile).exists()){ //katsotaan onko meille uutta komentotiedostoa
        QFile file(commandFile);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString komento = file.readLine().trimmed();
        file.remove();
        file.close();
        if(komento=="exit"){ //pyydetään sulkemaan tämä ohjelma
            QProcess lopetaSkripti;
            lopetaSkripti.start(projektiHakemisto+"/bin/tapasoitin"); //tapetaan eka soittimet jos niitä on? WTF ei pitäis olla täs vaihees soittimia??
            lopetaSkripti.waitForFinished();
            exit(0);
        }
    }
    ui->label->setText("  "+QTime::currentTime().toString());
    if(prosessi.pid()==0 && QMainWindow::isMinimized()){ //jos prosessi on 0 ja pääikkuna on pienennetty
        QMainWindow::showMaximized(); //pääikkuna suureksi
        QFile file (pidFile); //pid-filen saa poistaa nyt
        file.remove();
        tausta.updateLabel("");
    }
}

void MainWindow::on_listWidget_activated(const QModelIndex &index) //kun ikoni valitaan enter-painikkeella
{
    tausta.updateLabel("Loading: "+index.data().toString());
    QMainWindow::showMinimized();
    qDebug()<<"suoritetaan: "<< skripti.at(index.row());
    prosessi.start(skripti.at(index.row()));
    QFile file(pidFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QString sPid=QString::number(prosessi.pid());
    file.write(sPid.toUtf8());
    file.close();
}

void MainWindow::haeKonffi() //Tässä piirretään kuvakkeet ruudulle ja luetaan konffin parametrit.
{
    if(qApp->arguments().count() > 1){ //saatu komentoriviparametrina projektin hakemisto
        projektiHakemisto=qApp->arguments().at(1);
    }
    //qDebug()<<"projpath:"<<projektiHakemisto;
    QString kanavat=projektiHakemisto+"/channels.conf";
    //qDebug()<<"konffi:"<<kanavat;
    if (! QFile::exists(kanavat)){
        qCritical()<<"Virhe!"<<kanavat<<"ei löydy. Anna ohjelmalle argumenttina projektin päähakemisto, esim: cectv2 /home/pi/cectv2";
        exit(1);
    }
    QFile file(kanavat);
    QTextStream in(&file);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line = in.readLine();
    while (!line.isNull()) {
        if(line.length()>5){
            QStringList pieces = line.split("|");
            //qDebug()<<pieces[1];
            ui->listWidget->addItem(new QListWidgetItem(QIcon(projektiHakemisto+"/channels/"+pieces[1]),pieces[0]));
            skripti.append(projektiHakemisto+"/channels/"+pieces[2]);
        }
        line = in.readLine();
    }
    file.close();
}
