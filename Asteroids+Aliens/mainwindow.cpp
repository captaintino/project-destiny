#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>
#include<QTimer>
#include<QString>
#include<cmath>
#include <QCursor>
#include <QDesktopWidget>
#include <fstream>
#include <sstream>
#include <QKeyEvent>



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
    levelTimer->setInterval(30000);
    cheat = false;
    ui->lblLevel->setShown(false);
    ui->spinCheat->setShown(false);
    connect(levelTimer, SIGNAL(timeout()), this, SLOT(levelEnd()));
    highscores = new HighScores(&highScoreWindow);
    highscores->load();
    multiplayer = false;
    networked = false;
    userName="Player";
    connect(&clientWindow, SIGNAL(connected()), this, SLOT(connectedMultiplayer()));
    connect(&clientWindow, SIGNAL(disconnected()), this, SLOT(disconnectedMultiplayer()));
    freeze_game = false;
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

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(!freeze_game && fire){
        universe->getWorld(0)->userFires(universe->getShip());
        // Shoot a projectile
        qDebug("fire");
        fire = false;
        QTimer::singleShot(1000, this, SLOT(canFire()));
    }
}

void MainWindow::mainMenuSetShow(bool m)
{
    ui->btnStart->setShown(m);
    ui->btnCheat->setShown(m);
    ui->btnHighScores->setShown(m);
    ui->btnLoad->setShown(m);
    ui->btnInstructions->setShown(m);
    ui->lblLevel->setShown(m);
    ui->btnMultiplayer->setShown(m);
    ui->lblLevel->setShown(false);
    ui->spinCheat->setShown(false);
}

void MainWindow::on_btnStart_clicked()
{
    freeze_game = false;
    the_Score = new QLabel(this);
    the_Score->setGeometry(40,40,500,50); // Needs work *
    the_Score->setStyleSheet("QLabel { color : #df7121; font-size : 50px}");
    the_Score->raise();
    the_Score->show();
    mainMenuSetShow(false);
    ui->lnUsername->setShown(false);
    //this->grabMouse(); // <-- we need to have an <Esc> option...
    this->setCursor(Qt::BlankCursor);
    fire = true;
    QApplication::desktop()->cursor().setPos(340,520);
    if (cheat) {
        level = ui->spinCheat->value();
    } else {
        level = 1;
    }
    universe = new Universe(level, 0, cheat);
    clientWindow.updateUniverse(universe);
    highscores->setUniverse(universe);
    modelUpdater = new UniverseThread(universe, level);
    user = new Ship_Label(this, universe);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    for(int i = 0; i < 13; ++i)
    {
        objects.push_back(new on_screen_object(this,universe->getWorld(0),level, 0, 0, 0));
        connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
    }
    universe->getWorld(0)->lameToWalk();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
    updateTimer->start();
    levelTimer->start();
    modelUpdater->start();
    fireShot = new QTimer(this);
    QObject::connect(universe, SIGNAL(shipCrashed()), this, SLOT(userShipCrashed()));
    QObject::connect(universe, SIGNAL(projectileCreated()), this, SLOT(makeProjectile()));

    //Generating user projectiles...
    QObject::connect(universe, SIGNAL(userFires()), this, SLOT(osuCreationSlot()));
    //-----------------
    universe->save();
    highscores->setUserName(userName);
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
    for(int i=0; i<user_projectiles.size(); ++i)
    {
        user_projectiles.at(i)->update();
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
    if(!freeze_game)
    {
        accelerateBackground();
        universe->setLevel(level);
        universe->clearWorlds();
        universe->createWorlds();
        for(int i = 0; i < objects.size(); ++i){
            objects.at(i)->deleteLater();
        }
        for(int i = 0; i < projectiles.size(); ++i){
            projectiles.at(i)->deleteLater();
        }
        projectiles.clear();
        objects.clear();
        for(int i = 0; i < 13; ++i)
        {
            objects.push_back(new on_screen_object(this,universe->getWorld(0),level, 0, 0, 0));
            connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
        }
        modelUpdater->updateTimer(level);
        modelUpdater->start();
        universe->getWorld(0)->lameToWalk();
        updateTimer->start();

        //put UPDATE username score alive level
        if(multiplayer)
            clientWindow.sendUpdate(true);

        qDebug("Current Level is:" + QString::number(level).toAscii());
        levelTimer->start();
    }
}

void MainWindow::accelerateBackground()
{
    if(level % 2 == 0){
        backgroundTimer->setInterval(60 - (level / 2));
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
    if(!cheat)
        highscores->save();
    if(multiplayer)
        clientWindow.sendUpdate(false);
}

void MainWindow::makeProjectile()
{
    projectiles.push_back(new on_screen_object(this,universe->getWorld(0),level, universe->getWorld(0)->getLastProjectile()));
    //connect(projectiles.at(projectiles.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
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
    clientWindow.show();
    clientWindow.raise();
    clientWindow.activateWindow();
}

void MainWindow::on_btnLoad_clicked()
{
    freeze_game = false;
    ifstream infile("save.txt");

    if (!infile)
    {
        exit(1);
    }

    string str;
    getline(infile, str);
    stringstream line(str);
    line >> str;
    level = stoi(str);
    line >> str;
    int score = stoi(str);
    line >> str;
    int shipx = stoi(str);
    line >> str;
    int shipy = stoi(str);
    line >> str;
    int worldcount = stoi(str);
    line >> str;
    int asteroidcount = stoi(str);


    the_Score = new QLabel(this);
    the_Score->setGeometry(40,40,500,50); // Needs work *
    the_Score->setStyleSheet("QLabel { color : #df7121; font-size : 50px}");
    the_Score->raise();
    the_Score->show();
    fire = true;
    //this->grabMouse(); // <-- we need to have an <Esc> option...
    this->setCursor(Qt::BlankCursor);
    mainMenuSetShow(false);
    ui->lnUsername->setShown(false);
    QApplication::desktop()->cursor().setPos(shipx,shipy);
    universe = new Universe(level, score, cheat);
    clientWindow.updateUniverse(universe);
    highscores->setUniverse(universe);
    modelUpdater = new UniverseThread(universe, level);
    user = new Ship_Label(this, universe);
    QObject::connect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
    backgroundTimer->start();
    int offScreenCount = 0;

    stringstream check;
    check << line.rdbuf();
    for(int i = 0; i < asteroidcount; ++i)
    {
        check >> str;
        int x = stoi(str);
        check >> str;
        int y = stoi(str);
        if(y > 600 || y <= 0)
            offScreenCount++;
    }
    check >> str;
    int aliencount = stoi(str);
    for(int i = 0; i < aliencount; ++i)
    {
        check >> str;
        int x = stoi(str);
        check >> str;
        int y = stoi(str);
        if(y > 600 || y <= 0)
            offScreenCount++;
    }
    if(offScreenCount < 9)
    {
        for(int i = 0; i < asteroidcount; ++i)
        {
            line >> str;
            int x = stoi(str);
            line >> str;
            int y = stoi(str);
            if(y > 600 || y <= 0)
                offScreenCount++;
            objects.push_back(new on_screen_object(this,universe->getWorld(0),level, 1, x, y));
            connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
        }
        line >> str;
        int aliencount = stoi(str);
        for(int i = 0; i < aliencount; ++i)
        {
            line >> str;
            int x = stoi(str);
            line >> str;
            int y = stoi(str);
            if(y > 600 || y <= 0)
                offScreenCount++;
            objects.push_back(new on_screen_object(this,universe->getWorld(0),level, 2, x, y));
            connect(objects.at(objects.size()-1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
        }
    } else
    {
        levelEnd();
        levelFinished();
    }
    
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
    universe->getWorld(0)->lameToWalk();
    QObject::connect(universe, SIGNAL(shipCrashed()), this, SLOT(userShipCrashed()));
    QObject::connect(universe, SIGNAL(projectileCreated()), this, SLOT(makeProjectile()));
    updateTimer->start();
    modelUpdater->updateTimer(level);



    QTimer::singleShot(1000, this, SLOT(resumeLevel()));
    //resumeLevel();
    qDebug("Current Level is:" + QString::number(level).toAscii());
}

void MainWindow::resumeLevel(){
    modelUpdater->start();
    levelTimer->start();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    freeze_game = true;

    if (e->key() == Qt::Key_Escape) {
        if (!(universe->getShip()->isDead()) && !networked)
            universe->save();
        modelUpdater->terminate();
        updateTimer->stop();
        QObject::disconnect(updateTimer, SIGNAL(timeout()), this, SLOT(update_positions()));
        levelTimer->stop();
        backgroundTimer->stop();
        QObject::disconnect(backgroundTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));
        QObject::disconnect(universe, SIGNAL(projectileCreated()), this, SLOT(makeProjectile()));
        this->releaseMouse();
        this->setCursor(Qt::ArrowCursor);


        for (int i = 0; i < objects.size(); ++i) {
            objects.at(i)->deleteLater();
        }

        for(int i = 0; i < projectiles.size(); ++i){
            projectiles.at(i)->deleteLater();
        }
        projectiles.clear();
        objects.clear();
        the_Score->setShown(false);
        user->setShown(false);
        ui->label->setPixmap(QPixmap(":images/Main_Menu.jpg"));
        ui->lnUsername->setShown(true);
        mainMenuSetShow(true);
        ui->btnCheat->setText("Cheat Mode: OFF");
        cheat = false;
    }
}

void MainWindow::on_lnUsername_editingFinished()
{
    userName = ui->lnUsername->text();
    clientWindow.updateUsername(userName);
}

void MainWindow::connectedMultiplayer()
{
    multiplayer = true;
    networked = true;
    ui->btnLoad->setEnabled(false);
}

void MainWindow::disconnectedMultiplayer()
{
    multiplayer = false;
    networked = false;
    ui->btnLoad->setEnabled(true);
}

void MainWindow::canFire()
{
    //qDebug("signal Fired");
    fire = true;
}

void MainWindow::osuCreationSlot()
{
    Obstacle *proj = universe->getWorld(0)->getUserProjectile();
    user_projectiles.push_back(new on_screen_object(this, universe->getWorld(0), level, proj));
    //connect(user_projectiles.at(user_projectiles.size() - 1), SIGNAL(deleteMe()), this, SLOT(deleteLabel()));
}

