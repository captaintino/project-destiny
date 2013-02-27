#ifndef ALIEN_H
#define ALIEN_H
#include<obstacle.h>

class Alien : public Obstacle
{
public:
    Alien();

    void move();
};

#endif // ALIEN_H
