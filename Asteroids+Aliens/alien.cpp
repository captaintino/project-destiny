#include "alien.h"

#include<obstacle.h>
Alien::Alien(int initx, int inity):Obstacle(initx, inity, 60, 61, ":/images/asteroid.png")
{
    /*
    x=initx;
    y=inity;
    //image width and height...
    w = 61;
    h = 60;
    type = ":/images/ALIEN_IMAGE.png";
    */
}

void Alien::move()
{
    y+=2;
}

std::string Alien::save()
{
}
