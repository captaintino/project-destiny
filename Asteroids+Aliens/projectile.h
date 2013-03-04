#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <obstacle.h>

class Projectile:public Obstacle
{
public:
    Projectile(int initx, int inity);

    void move();
};

#endif // PROJECTILE_H
