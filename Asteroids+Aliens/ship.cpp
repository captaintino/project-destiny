#include "ship.h"
#include<QMouseEvent>

Ship::Ship()
{
}

void Ship::mouseMoveEvent(QMouseEvent *ev){
    this->setGeometry(ev->x(),ev->y(),width(),height());
}
