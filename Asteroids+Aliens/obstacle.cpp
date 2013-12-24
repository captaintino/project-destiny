#include "obstacle.h"

Obstacle::Obstacle(int initx, int inity, int inith, int initw, QString inittype, int initspeed): x(initx), y(inity), h(inith), w(initw), speed(initspeed), type(inittype){ isAlive = true;}
int Obstacle::getX(){ return x;}
int Obstacle::getY(){ return y;}
int Obstacle::getH(){ return h;}
int Obstacle::getW(){ return w;}
QString Obstacle::getType(){ return type;}
