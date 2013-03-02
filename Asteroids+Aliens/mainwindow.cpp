#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>
#include<QTimer>
#include<QString>
#include<cmath>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    backgroundTimer = new QTimer(this);
    backgroundTimer->setInterval(33);
    background_counter = 1;
    itemSpawn = new QThread(this);
    connect(itemSpawn, SIGNAL(started()), this, SLOT(spawnItems()));
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
    level = 1;
    universe = new Universe(level);
    user = new Ship_Label(this);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    // Must be done last
    //itemSpawn->start(); ???
    for(int i = 0; i < 13; ++i){
        objects[i] = new on_screen_object(this, this->universe->getWorld(0), level);
        //sleep(1000/sqrt(level));
    }
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

void MainWindow::spawnItems()
{
    for(int i = 0; i < 13; ++i){
        objects[i] = new on_screen_object(this, this->universe->getWorld(1), level);
        sleep(1000/sqrt(level));
    }
}
