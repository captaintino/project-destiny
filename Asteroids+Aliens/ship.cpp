#include "ship.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>

Ship::Ship(QWidget *parent): QLabel(parent), fire(true)
{
    setGeometry(380, 540, 40, 40);
    grabMouse();
    setScaledContents(true);
    QPixmap img(":/images/test.jpg");
    setPixmap(img);
    show();
}

void Ship::mouseMoveEvent(QMouseEvent *ev)
{
    this->setGeometry(ev->x(),ev->y(),width(),height());
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
