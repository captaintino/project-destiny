#ifndef SHIP_H
#define SHIP_H
#include<QLabel>
#include<QTimer>

class Ship : public QLabel
{
    QTimer fireShot;
    bool fire;
public:
    Ship(QWidget * parent);

    // Mouse events
    void mouseMoveEvent(QMouseEvent *ev);

    void mousePressEvent(QMouseEvent *ev);

    // Saves the item state
    std::string save();

private slots:
    void canFire();
};

#endif // SHIP_H
