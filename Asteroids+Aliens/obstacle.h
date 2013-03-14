#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QString>

class Obstacle
{
protected:
    int x,y,h,w,speed;
    bool isAlien;
    QString type;
public:
    Obstacle(int initx, int inity, int inith, int initw, QString inittype, int initspeed);

    //Getter methods
    virtual int getX();
    virtual int getY();
    virtual int getH();
    virtual int getW();
    virtual QString getType();

    virtual void move() = 0;

    virtual void setSpeed(int newSpeed) { speed = newSpeed; }

    virtual std::string save() = 0;
};

#endif // OBSTACLE_H
