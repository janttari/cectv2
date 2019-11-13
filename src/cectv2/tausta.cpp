#include "tausta.h"
#include "ui_tausta.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QTime>

Tausta::Tausta(QWidget *parent) : QWidget(parent), ui(new Ui::Tausta)
{
    ui->setupUi(this);
    Tausta::move(QPoint(0,0)); //siirretään ikkuna vasempaan yläkulmaan
    Tausta::setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::CustomizeWindowHint | Qt::FramelessWindowHint|Qt::SplashScreen);
    QDesktopWidget* widget = qApp->desktop(); //etsitään näytön koko
    QRect screenSize = widget->availableGeometry(widget->primaryScreen());
    int xkoko = screenSize.width();
    int ykoko = screenSize.height();
    Tausta::setFixedWidth(xkoko); //laitetaan koko näytön levyiseksi
    Tausta::setFixedHeight(ykoko); //laitetaan korkeus xx pikseliä

    ui->label->move(40,30);
    ui->label->setFixedHeight(ykoko);
    ui->label->setFixedWidth(xkoko);

    QTimer *timer = new QTimer(this);                           //Luodaan uusi timer
    connect(timer, SIGNAL(timeout()), this, SLOT(kello()));
    timer->start(100);
}

Tausta::~Tausta()
{
    delete ui;
}

void Tausta::kello() //timerin event
{

    //ui->label->setText("localhost "+QTime::currentTime().toString());
}

void Tausta::updateLabel(QString label)
{
    ui->label->setText(label);
}
