#include "ship.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include<cstring>
#include<QString>
Ship::Ship(QWidget *parent): QLabel(parent), fire(true), window(parent)
{
    setGeometry(380, 540, 40, 40);
    grabMouse();
    setScaledContents(true);
    QPixmap img(":/images/test.jpg");
    setPixmap(img);
    show();
    setMouseTracking(true);
    updateShip = new QTimer(this);
    fireShot = new QTimer(this);
    QObject::connect(updateShip, SIGNAL(timeout()), this, SLOT(shipToMouse()));
    updateShip->start(10);
}

void Ship::shipToMouse()
{
    qDebug("Fire");
    this->setGeometry(window->cursor().pos().x() - 100, window->cursor().pos().y() - 100,width(),height());
}

void Ship::mouseMoveEvent(QMouseEvent *ev)
{

}

void Ship::mousePressEvent(QMouseEvent *ev)
{
    if(fire){
        // Shoot a projectile
        fire = false;
        fireShot->singleShot(1000, this, SLOT(canFire()));
    }
}

void Ship::canFire()
{
    fire = true;
}
