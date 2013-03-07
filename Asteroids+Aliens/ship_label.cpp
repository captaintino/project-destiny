#include "ship_label.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include<cstring>
#include<QString>
Ship_Label::Ship_Label(QWidget *parent): QLabel(parent), fire(true), window(parent)
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
    updateShip->start(10);
}

void Ship_Label::shipToMouse()
{
    this->setGeometry(window->cursor().pos().x() - 90, window->cursor().pos().y() - 90,width(),height());
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
