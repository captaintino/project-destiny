#include "asteroid.h"

Asteroid::Asteroid(int initx, int inity, int initspeed):Obstacle(initx, inity, 60, 61, ":/images/asteroid.png", initspeed)
{
}

void Asteroid::move()
{
    y+=speed;
}

std::string Asteroid::save()
{
}
