#ifndef ASTEROID_H
#define ASTEROID_H
#include<obstacle.h>

class Asteroid : public Obstacle
{
public:
    Asteroid(int initx, int inity, int initspeed = 8);

    // Move the item down the screen
    void move();

    // Saves the item state
    std::string save();
};

#endif // ASTEROID_H
