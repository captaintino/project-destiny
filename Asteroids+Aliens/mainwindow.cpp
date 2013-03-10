#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>
#include<QTimer>
#include<QString>
#include<cmath>
#include <QCursor>
#include <QDesktopWidget>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    backgroundTimer = new QTimer(this);
    backgroundTimer->setInterval(33);
    background_counter = 1;
    updateTimer = new QTimer(this);
    updateTimer->setInterval(33);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    //this->grabMouse(); // <-- we'll add this back once we have an <Esc> option...
    //this->cursor().setShape(Qt::BlankCursor);
    QApplication::desktop()->cursor().setPos(0,0);
    level = 1;
    universe = new Universe(level);
    user = new Ship_Label(this, universe->getWorld(0));
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    for(int i = 0; i < 13; ++i)
    {
        objects[i] = new on_screen_object(this,universe->getWorld(0),level);
    }
    universe->getWorld(0)->lameToWalk();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
    updateTimer->start();
    QObject::connect(universe->getWorld(0), SIGNAL(shipCrashed()), this, SLOT(userShipCrashed()));
}


void MainWindow::rotateBackground()
{
    if(background_counter > 39)
        background_counter = 1;
    ui->label->setPixmap(":/images/background/" + QString::number(background_counter)+ ".jpg");

    ++background_counter;
}

void MainWindow::update_positions()
{
    for(int i=0; i<13; ++i)
    {
        objects[i]->update();
    }
}

void MainWindow::userShipCrashed()
{
    updateTimer->disconnect();
    user->crashed();
    backgroundTimer->disconnect();
    qDebug("Exiting update... user has crashed.");
}



void MainWindow::on_btnInstructions_clicked()
{
    instructionWindow.show();
    instructionWindow.raise();
    instructionWindow.activateWindow();
}
