#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<QLabel>

class Obstacle : public QLabel
{
public:
    Obstacle();

    virtual void move() = 0;
};

#endif // OBSTACLE_H
