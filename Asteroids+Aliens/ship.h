#ifndef SHIP_H
#define SHIP_H

class Ship
{
private:
    int x, y;
    bool hit;
public:
    Ship();

    //Getter methods...
    int getX(){return x;}
    int getY(){return y;}

    //Setter methods...
    void setX(int newX) { x = newX;}
    void setY(int newY) { y = newY;}
    void setHit(bool updateVal) { hit = updateVal;}
};

#endif // SHIP_H
