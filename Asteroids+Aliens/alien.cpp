#include "alien.h"

#include<obstacle.h>
Alien::Alien(int initx, int inity, int initspeed):Obstacle(initx, inity, 60, 61, ":/images/alien.png", initspeed)
{
    isAlive = true;
   //Remember to get an alien image eventually....
}

void Alien::move()
{
    y+=speed;
}

std::string Alien::save()
{
}
