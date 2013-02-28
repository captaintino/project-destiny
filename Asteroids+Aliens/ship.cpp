#include "ship.h"
#include<QMouseEvent>
#include<QLabel>

Ship::Ship(QWidget *parent): QLabel(parent)
{
    setGeometry(380, 540, 40, 40);
    grabMouse();
    setScaledContents(true);
    QPixmap img(":/images/test.jpg");
    setPixmap(img);
    show();
}

void Ship::mouseMoveEvent(QMouseEvent *ev){
    this->setGeometry(ev->x(),ev->y(),width(),height());
}
