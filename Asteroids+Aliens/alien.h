#ifndef ALIEN_H
#define ALIEN_H
#include<obstacle.h>

class Alien : public Obstacle
{
public:
    Alien(int initx, int inity, int initspeed = 10);

    // Move the item down the screen
    void move();
    void Kill() { isAlive = false; }

    // Saves the item state
    std::string save();
};

#endif // ALIEN_H
