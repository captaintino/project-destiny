#ifndef SHIP_LABEL_H
#define SHIP_LABEL_H
#include<QLabel>
#include<QTimer>
#include<universe.h>
#include<world.h>

class Ship_Label : public QLabel
{
    Q_OBJECT
    QTimer * updateShip;
    QWidget * window;
    Universe * this_Universe;
    int ship_frame;

public:
    Ship_Label(QWidget * parent, Universe * get_universe);


    void crashed();
    void updateCoords();


    // Saves the item state
    std::string save();

public slots:

    void shipToMouse();
    void expAnimate();


};

#endif // SHIP_LABEL_H
