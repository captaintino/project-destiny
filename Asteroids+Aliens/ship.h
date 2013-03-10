#ifndef SHIP_H
#define SHIP_H

class Ship
{
private:
    int x, y, w, h;
    bool hit;
public:
    Ship();

    //Getter methods...
    int getX(){return x;}
    int getY(){return y;}
    int getW(){return w;}
    int getH(){return h;}

    //Setter methods...
    void setCoords(int new_x, int new_y, int new_w, int new_h)
    {
        x = new_x;
        y = new_y;
        w = new_w;
        h = new_h;
    }
    void setHit(bool updateVal) { hit = updateVal;}


};

#endif // SHIP_H
