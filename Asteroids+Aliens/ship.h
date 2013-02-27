#ifndef SHIP_H
#define SHIP_H
#include<QLabel>

class Ship : public QLabel
{
public:
    Ship();

    // Mouse events
    void mouseMoveEvent(QMouseEvent *ev);

};

#endif // SHIP_H
