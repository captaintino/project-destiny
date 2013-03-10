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

public:
    Ship_Label(QWidget * parent, World * get_world);

    void mousePressEvent(QMouseEvent *ev);
    void crashed();


    // Saves the item state
    std::string save();

private slots:
    void canFire();
    void shipToMouse();
};

#endif // SHIP_LABEL_H
