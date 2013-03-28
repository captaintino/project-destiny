#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <obstacle.h>

class Projectile:public Obstacle
{
public:
    Projectile(int initx, int inity);

    void move();
    void explode(){ isAlive = false; }

    std::string save() {}
};

#endif // PROJECTILE_H
