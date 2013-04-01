#include "projectile.h"

Projectile::Projectile(int initx, int inity):Obstacle(initx, inity, 50, 5, ":/images/projectile.png", 15) //We need to come back and make this level adjusted.
{
}

void Projectile::move()
{
    y+=speed;
    // delete this guy and make a new guy show up
}

void Projectile::setType(std::string newType)
{
    type=newType;
}
