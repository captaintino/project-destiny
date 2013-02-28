#include "ship.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<QDebug>

Ship::Ship(QWidget *parent): QLabel(parent), fire(true)
{
    setGeometry(380, 540, 40, 40);
    grabMouse();
    setScaledContents(true);
    QPixmap img(":/images/test.jpg");
    setPixmap(img);
    show();
    setMouseTracking(true);
}

void Ship::mouseMoveEvent(QMouseEvent *ev)
{
    this->setGeometry(ev->pos().x() - 20,ev->pos().y() + 20,width(),height());
}

void Ship::mousePressEvent(QMouseEvent *ev)
{
    if(fire){
        // Shoot a projectile
        fire = false;
        fireShot.singleShot(1000, this, SLOT(canFire()));
    }
}

void Ship::canFire()
{
    fire = true;
}
