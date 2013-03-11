#ifndef SHIP_LABEL_H
#define SHIP_LABEL_H
#include<QLabel>
#include<QTimer>
#include<universe.h>
#include<world.h>

class Ship_Label : public QLabel
{
    Q_OBJECT
    QTimer * fireShot, * updateShip;
    bool fire;
    QWidget * window;
    World * this_world;
    int ship_frame;

public:
    Ship_Label(QWidget * parent, World * get_world);

    void mousePressEvent(QMouseEvent *ev);
    void crashed();
    void updateCoords();


    // Saves the item state
    std::string save();

private slots:
    void canFire();
    void shipToMouse();
    void expAnimate();


};

#endif // SHIP_LABEL_H
