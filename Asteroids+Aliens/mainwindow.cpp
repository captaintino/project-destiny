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
    backgroundTimer->setInterval(60);
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
    the_Score = new QLabel(this);
    the_Score->setGeometry(40,40,500,50); // Needs work *
    the_Score->setStyleSheet("QLabel { color : yellow; font-size : 50px}");
    the_Score->show();
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    ui->btnInstructions->setShown(false);
    //this->grabMouse(); // <-- we need to have an <Esc> option...
    //this->setCursor(Qt::BlankCursor);
    QApplication::desktop()->cursor().setPos(340,520);
    level = 1;
    universe = new Universe(level);
    modelUpdater = new UniverseThread(universe, level);
    user = new Ship_Label(this, universe);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    for(int i = 0; i < 13; ++i)
    {
        objects.push_back(new on_screen_object(this,universe->getWorld(0),level));
        connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
    }
    universe->getWorld(0)->lameToWalk();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
    updateTimer->start();
    levelTimer->start();
    modelUpdater->start();
    QObject::connect(universe, SIGNAL(shipCrashed()), this, SLOT(userShipCrashed()));
}


void MainWindow::rotateBackground()
{
    if(background_counter > 39)
        background_counter = 1;
    ui->label->setPixmap(":/images/background/" + QString::number(background_counter)+ ".jpg");
    ui->label->setMouseTracking(false);
    ++background_counter;
}

void MainWindow::update_positions()
{
    user->updateCoords();
    for(int i=0; i<objects.size(); ++i)
    {
        objects.at(i)->update();
    }
    QString num = QString::number(universe->getScore());
    int numSize = num.size();
    for(int i = 1; i < (numSize / 3.0); ++i){
        num.insert(numSize - (i * 3), ',');
    }
    the_Score->setText(num);
}

void MainWindow::levelEnd()
{
    levelTimer->stop();
    for(int i = 0; i < objects.size(); ++i){
        objects.at(i)->setLevelOver();
    }
}

void MainWindow::levelFinished()
{
    updateTimer->stop();

    modelUpdater->terminate(); // Not sure if this is the right method

    ++level;
    // bakground speedup
    universe->setLevel(level);
    universe->clearWorlds();
    universe->createWorlds();
    objects.clear();
    for(int i = 0; i < 13; ++i)
    {
        objects.push_back(new on_screen_object(this,universe->getWorld(0),level));
        connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
    }
    modelUpdater->updateTimer(level);
    modelUpdater->start();
    universe->getWorld(0)->lameToWalk();
    updateTimer->start();
    qDebug("Current Level is:" + QString::number(level).toAscii());
    levelTimer->start();
}

void MainWindow::accelerateBackground()
{
    if(level % 2 == 0){
        backgroundTimer->setInterval(backgroundTimer->interval() - 1);
    }
}

void MainWindow::userShipCrashed()
{
    modelUpdater->terminate();
    updateTimer->stop();
    levelTimer->stop();
    user->crashed();
    backgroundTimer->stop();
    this->releaseMouse();
    this->setCursor(Qt::ArrowCursor);
    qDebug("Exiting update... user has crashed.");
}

void MainWindow::deleteLabel()
{
    for(int i = 0; i < objects.size(); ++i){
        if(objects.at(i) == sender()){
            sender()->deleteLater();
            objects.erase(objects.begin() + i);
            break;
        }
    }
    if(objects.size()<1){
        QTimer::singleShot(500, this, SLOT(levelFinished()));
    }
}



void MainWindow::on_btnInstructions_clicked()
{
    instructionWindow.show();
    instructionWindow.raise();
    instructionWindow.activateWindow();
}

void MainWindow::on_btnHighScores_clicked()
{
    highScoreWindow.show();
    highScoreWindow.raise();
    highScoreWindow.activateWindow();
}
