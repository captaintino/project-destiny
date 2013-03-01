#include "asteroid.h"
#include<QPixmap>

Asteroid::Asteroid(QWidget *parent, int initx, int inity): Obstacle(parent)
{
    setGeometry(initx, inity, 61, 60);
    setScaledContents(true);
    QPixmap img(":/images/asteroid.png");
    setPixmap(img);
    show();
}

void Asteroid::move()
{
    this->setGeometry(x(), y() + 2, width(), height());
    if(y() > 660){
        // delete this guy and make a new guy show up
    }
}

std::string Asteroid::save()
{
}
