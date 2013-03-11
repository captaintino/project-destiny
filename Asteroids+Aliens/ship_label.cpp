#include "ship_label.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include<cstring>
#include<QString>
Ship_Label::Ship_Label(QWidget *parent, Universe *get_universe): QLabel(parent), fire(true), window(parent), this_Universe(get_universe)
{
    setGeometry(380, 540, 40, 40);
    setScaledContents(true);
    QPixmap img(":/images/Player_Ship.png");
    setPixmap(img);
    show();
    setMouseTracking(true);
    updateShip = new QTimer(this);
    fireShot = new QTimer(this);
    QObject::connect(updateShip, SIGNAL(timeout()), this, SLOT(shipToMouse()));
    //QObject::connect(this_world, SIGNAL(shipCrashed()), this, SLOT(crashed()));
    updateShip->start(10);
    this_Universe->setUserShip(this->x(), this->y(), this->width(), this->height());
}

void Ship_Label::shipToMouse()
{
    //this->setGeometry(window->cursor().pos().x() - 90, window->cursor().pos().y() - 100, width(), height());
    this_Universe->setUserShip(window->cursor().pos().x() - 90, window->cursor().pos().y() - 90, this->width(), this->height());

}

void Ship_Label::updateCoords()
{
    this->setGeometry(this_Universe->getShip()->getX(), this_Universe->getShip()->getY(), this->width(), this->height());
}

void Ship_Label::crashed()
{
    updateShip->disconnect();
    updateShip->setInterval(30);
    QObject::connect(updateShip, SIGNAL(timeout()), this, SLOT(expAnimate()));
    qDebug("Ship Crashed!");
}

void Ship_Label::expAnimate()
{
    if(ship_frame > 39)
        ship_frame = 1;
    this->setPixmap(":/images/explosion/shipExp" + QString::number(ship_frame) + ".png");
    setGeometry(this->x(), this->y(), 80, 80);

    ++ship_frame;

}


void Ship_Label::mousePressEvent(QMouseEvent *ev)
{
    if(fire){
        // Shoot a projectile
        qDebug("fire");
        fire = false;
        QTimer::singleShot(1000, this, SLOT(canFire()));
    }
}

void Ship_Label::canFire()
{
    qDebug("signal Fired");
    fire = true;
}
