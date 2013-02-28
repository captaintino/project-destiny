#include "alien.h"

Alien::Alien(QWidget * parent, int initx, int inity): Obstacle(parent)
{
    setGeometry(initx, inity, 61, 60);
    setScaledContents(true);
    QPixmap img(":/ALIENIMAGE.jpg");
    setPixmap(img);
}

void Alien::move()
{
    this->setGeometry(x(), y() + 2, width(), height());
    if(y() > 660){
        // delete this guy and make a new guy show up
    }
}

std::string Alien::save()
{
}
