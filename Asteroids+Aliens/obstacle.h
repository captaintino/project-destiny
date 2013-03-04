#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QString>

class Obstacle
{
protected:
    int x,y,h,w;
    QString type;
public:
    Obstacle(int initx, int inity, int inith, int initw, QString inittype);

    //Getter methods
    virtual int getX();
    virtual int getY();
    virtual int getH();
    virtual int getW();
    virtual QString getType();

    virtual void move() = 0;

    virtual std::string save() = 0;
};

#endif // OBSTACLE_H
