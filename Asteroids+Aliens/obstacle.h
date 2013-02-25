#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<QLabel>

class Obstacle : public QLabel
{
public:
    Obstacle(QWidget * parent):QLabel(parent){}

    virtual void move() = 0;

    virtual std::string save() = 0;
};

#endif // OBSTACLE_H
