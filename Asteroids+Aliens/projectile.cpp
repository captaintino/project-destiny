#include "projectile.h"

Projectile::Projectile(int initx, int inity):Obstacle(initx, inity, 60, 61, ":/images/asteroid.png", 4)
{
}

void Projectile::move()
{
    y+=speed;
        // delete this guy and make a new guy show up

}
