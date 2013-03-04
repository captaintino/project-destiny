#ifndef SHIP_LABEL_H
#define SHIP_LABEL_H
#include<QLabel>
#include<QTimer>

class Ship_Label : public QLabel
{
    Q_OBJECT
    QTimer * fireShot, * updateShip;
    bool fire;
    QWidget * window;
public:
    Ship_Label(QWidget * parent);

    void mousePressEvent(QMouseEvent *ev);

    // Saves the item state
    std::string save();

private slots:
    void canFire();
    void shipToMouse();
};

#endif // SHIP_LABEL_H
