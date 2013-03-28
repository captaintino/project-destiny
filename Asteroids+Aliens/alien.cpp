#include "alien.h"

#include<obstacle.h>
Alien::Alien(int initx, int inity, int initspeed):Obstacle(initx, inity, 60, 61, ":/images/alien.png", initspeed)
{
}

void Alien::move()
{
    y+=speed;
}

std::string Alien::save()
{
}
