#include "asteroid.h"

Asteroid::Asteroid()
{
}

void Asteroid::move()
{
    this->setGeometry(x(), y() + 2, width(), height());
    if(y() > 660){
        // delete this guy and make a new guy show up
    }
}
