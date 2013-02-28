#ifndef ASTEROID_H
#define ASTEROID_H
#include<obstacle.h>

class Asteroid : public Obstacle
{
public:
    Asteroid(QWidget * parent, int initx, int inity);

    // Move the item down the screen
    void move();

    // Saves the item state
    std::string save();
};

#endif // ASTEROID_H
