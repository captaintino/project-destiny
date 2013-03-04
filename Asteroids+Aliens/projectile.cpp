#include "projectile.h"

Projectile::Projectile(int initx, int inity):Obstacle(initx, inity, 60, 61, ":/images/asteroid.png")
{
}

void Projectile::move()
{
    y+=5;
        // delete this guy and make a new guy show up

}
