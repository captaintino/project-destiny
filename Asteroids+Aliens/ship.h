#ifndef SHIP_H
#define SHIP_H

class Ship
{
private:
    int x, y, w, h;
    int nextX, nextY;
    bool hit;
public:
    Ship();

    //Getter methods...
    int getX(){return x;}
    int getY(){return y;}
    int getW(){return w;}
    int getH(){return h;}
    bool isDead(){return hit;}

    //Setter methods...
    void setCoords(int new_x, int new_y, int new_w, int new_h);

    void updateCoords();

    void setHit(bool updateVal) { hit = updateVal;}


};

#endif // SHIP_H
