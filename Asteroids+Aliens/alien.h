#ifndef ALIEN_H
#define ALIEN_H
#include<obstacle.h>

class Alien : public Obstacle
{
public:
    Alien(QWidget *parent, int initx, int inity);

    void move();
};

#endif // ALIEN_H
