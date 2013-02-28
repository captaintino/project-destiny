#ifndef ASTEROID_H
#define ASTEROID_H
#include<obstacle.h>

class Asteroid : public Obstacle
{
public:
    Asteroid(QWidget * parent, int initx, int inity);

    void move();
};

#endif // ASTEROID_H
