#include "projectile.h"

Projectile::Projectile()
{
}

void Projectile::move()
{
    this->setGeometry(x(), y() + 2, width(), height());
    if(y() > 605){
        // delete this guy and make a new guy show up
    }
}
