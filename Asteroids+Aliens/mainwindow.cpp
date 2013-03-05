#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>
#include<QTimer>
#include<QString>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    backgroundTimer = new QTimer(this);
    backgroundTimer->setInterval(33);
    background_counter = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectWorldTimer(QTimer * t)
{
    connect(t, SIGNAL(timeout()), this, SLOT(worldClick()));
}



void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    this->cursor().setPos(380, 540);
    universe = new Universe(1);
    user = new Ship_Label(this);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
}

void MainWindow::worldClick(){
    universe->move();
}

void MainWindow::rotateBackground()
{
    if(background_counter > 39)
        background_counter = 1;
    ui->label->setPixmap(":/images/background/" + QString::number(background_counter)+ ".jpg");

    ++background_counter;
}
