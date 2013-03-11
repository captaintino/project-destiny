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
    levelTimer = new QTimer(this);
    levelTimer->setInterval(10000);
    connect(levelTimer, SIGNAL(timeout()), this, SLOT(levelEnd()));
}

MainWindow::~MainWindow()
{
    delete ui;
    modelUpdater->terminate();
    backgroundTimer->deleteLater();
    updateTimer->deleteLater();
    levelTimer->deleteLater();
    delete universe;
    user->deleteLater();
    modelUpdater->deleteLater();
    for(int i = 0; i < objects.size(); ++i){
        delete objects.at(i);
    }
}

void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    ui->btnInstructions->setShown(false);
    this->grabMouse(); // <-- we need to have an <Esc> option...
    this->setCursor(Qt::BlankCursor);
    QApplication::desktop()->cursor().setPos(0,0);
    level = 1;
    universe = new Universe(level);
    modelUpdater = new UniverseThread(universe, level);
    user = new Ship_Label(this, universe);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    for(int i = 0; i < 13; ++i)
    {
        objects.push_back(new on_screen_object(this,universe->getWorld(0),level));
    }
    universe->getWorld(0)->lameToWalk();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
    updateTimer->start();
    levelTimer->start();
    modelUpdater->start();
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
    user->updateCoords();
    for(int i=0; i<objects.size(); ++i)
    {
        objects.at(i)->update();
    }
}

void MainWindow::levelEnd()
{
    updateTimer->stop();
    for(int i = 0; i < objects.size();){
        objects.at(i)->deleteLater();
        objects.erase(objects.begin());
    }

    modelUpdater->terminate(); // Not sure if this is the right method

    ++level;
    universe->setLevel(level);
    universe->clearWorlds();
    universe->createWorlds();
    for(int i = 0; i < 13; ++i)
    {
        objects.push_back(new on_screen_object(this,universe->getWorld(0),level));
    }
    modelUpdater->updateTimer(level);
    modelUpdater->start();
    universe->getWorld(0)->lameToWalk();
    updateTimer->start();
    qDebug("Current Level is:" + QString::number(level).toAscii());
}

void MainWindow::userShipCrashed()
{
    updateTimer->disconnect();
    modelUpdater->terminate();
    user->crashed();
    backgroundTimer->disconnect();
    this->releaseMouse();
    this->setCursor(Qt::ArrowCursor);
    qDebug("Exiting update... user has crashed.");
}



void MainWindow::on_btnInstructions_clicked()
{
    instructionWindow.show();
    instructionWindow.raise();
    instructionWindow.activateWindow();
}
