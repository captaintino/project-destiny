#include "ship.h"

Ship::Ship():x(380), y(540), h(40), w(40), hit(false)
{
//    x = 380;
//    y = 540;
//    h = 40;
//    w = 40;
//    hit = false;
}

void Ship::setCoords(int new_x, int new_y, int new_w, int new_h)
{
    nextX = new_x;
    nextY = new_y;
    w = new_w;
    h = new_h;
}

void Ship::updateCoords()
{
    x = nextX;
    y = nextY;
}




