#include "ship_label.h"
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include<cstring>
#include<QString>
#include <QSound>


Ship_Label::Ship_Label(QWidget *parent, Universe *get_universe): QLabel(parent), window(parent), this_Universe(get_universe)
{
    setGeometry(380, 540, 40, 40);
    setScaledContents(true);
    QPixmap img(":/images/Player_Ship.png");
    setPixmap(img);
    show();
    setMouseTracking(true);
    updateShip = new QTimer(this);
    QObject::connect(updateShip, SIGNAL(timeout()), this, SLOT(shipToMouse()));
    //QObject::connect(this_world, SIGNAL(shipCrashed()), this, SLOT(crashed()));
    updateShip->start(10);
    this_Universe->setUserShip(this->x(), this->y(), this->width(), this->height());
}

void Ship_Label::shipToMouse()
{
    if ((window->cursor().pos().x() - 90) > 765) {
        this_Universe->setUserShip(765, window->cursor().pos().y() - 90,width(),height());
    } else if ((window->cursor().pos().x() - 90) < 0) {
        this_Universe->setUserShip(0, window->cursor().pos().y() - 90, width(), height());
    } else if ((window->cursor().pos().y() - 100) > 560){
        //this_Universe->setUserShip(window->cursor().pos().x() - 90, 560, width(), height());
    } else {
        this_Universe->setUserShip(window->cursor().pos().x() - 90,
            window->cursor().pos().y() - 100, this->width(), this->height());
    }
    //this->setGeometry(window->cursor().pos().x() - 90, window->cursor().pos().y() - 100, width(), height());
    //this_Universe->setUserShip(window->cursor().pos().x() - 90, window->cursor().pos().y() - 90, this->width(), this->height());

}

void Ship_Label::updateCoords()
{
    this->setGeometry(this_Universe->getShip()->getX(), this_Universe->getShip()->getY(), this->width(), this->height());
}

void Ship_Label::crashed()
{
    this->raise();
    updateShip->disconnect();
    updateShip->setInterval(30);
    QObject::connect(updateShip, SIGNAL(timeout()), this, SLOT(expAnimate()));
    qDebug("Ship Crashed!");
    //QSound::play("explosion.wav"); //non-functional and very frustrating.
}

void Ship_Label::expAnimate()
{
    if(ship_frame > 39)
        ship_frame = 1;
    this->setPixmap(":/images/explosion/shipExp" + QString::number(ship_frame) + ".png");
    setGeometry(this->x(), this->y(), 40, 40);

    ++ship_frame;

}
