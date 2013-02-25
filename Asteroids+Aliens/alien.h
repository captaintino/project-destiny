#ifndef ALIEN_H
#define ALIEN_H
#include<obstacle.h>

class Alien : public Obstacle
{
public:
    Alien(QWidget *parent, int initx, int inity);

    // Move the item down the screen
    void move();

    // Saves the item state
    std::string save();
};

#endif // ALIEN_H
