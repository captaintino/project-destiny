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
    cheat = false;
    ui->lblLevel->setShown(false);
    ui->spinCheat->setShown(false);
    connect(levelTimer, SIGNAL(timeout()), this, SLOT(levelEnd()));
    connect(levelTimer,SIGNAL(timeout()), this, SLOT(on_levelTimer_finished()));
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
    the_Score->setStyleSheet("QLabel { color : #df7121; font-size : 50px}");
    the_Score->raise();
    the_Score->show();
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    ui->btnInstructions->setShown(false);
    ui->spinCheat->setShown(false);
    ui->lblLevel->setShown(false);
    ui->btnMultiplayer->setShown(false);
    //this->grabMouse(); // <-- we need to have an <Esc> option...
    //this->setCursor(Qt::BlankCursor);
    QApplication::desktop()->cursor().setPos(340,520);
    if (cheat) {
        level = ui->spinCheat->value();
    } else {
        level = 1;
    }
    universe = new Universe(level, cheat);
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
    QObject::connect(universe, SIGNAL(projectileCreated()), this, SLOT(makeProjectile()));
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
    for(int i=0; i<projectiles.size(); ++i)
    {
        projectiles.at(i)->update();
    }
    QString num = QString::number(universe->getScore());
    int numSize = num.size();
    for(int i = 1; i < (numSize / 3.0); ++i){
        num.insert(numSize - (i * 3), ',');
    }
    the_Score->raise();
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
    for(int i = 0; i < projectiles.size(); ++i){
        projectiles.at(i)->deleteLater();
    }
    projectiles.clear();
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
    highscores->save();
}

void MainWindow::makeProjectile()
{
    projectiles.push_back(new on_screen_object(this,universe->getWorld(0),level, universe->getWorld(0)->getLastProjectile()));
    connect(projectiles.at(projectiles.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
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
        //put UPDATE username score alive level
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
    highscores->display();
    highScoreWindow.show();
    highScoreWindow.raise();
    highScoreWindow.activateWindow();
}

void MainWindow::on_btnCheat_clicked()
{
    if (ui->btnCheat->text() == "Cheat Mode: OFF") {
        ui->btnCheat->setText("Cheat Mode: ON");
        cheat = true;
        ui->lblLevel->setShown(true);
        ui->spinCheat->setShown(true);
    } else {
        ui->btnCheat->setText("Cheat Mode: OFF");
        cheat = false;
        ui->lblLevel->setShown(false);
        ui->spinCheat->setShown(false);
    }

}

void MainWindow::on_btnMultiplayer_clicked()
{

}

void MainWindow::on_btnLoad_clicked()
{
    highscores->load();
}

void MainWindow::on_levelTimer_finished()
{
    highscores->save();
}
