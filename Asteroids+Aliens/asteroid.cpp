#include "asteroid.h"

Asteroid::Asteroid(int initx, int inity):Obstacle(initx, inity, 60, 61, ":/images/asteroid.png")
{
    /*
    x=initx;
    y=inity;
    //image witdth and height
    w = 61;
    h = 60;
    type = ":/images/asteroid.png";
    */
}

void Asteroid::move()
{
    y+=2;
}

std::string Asteroid::save()
{
}
