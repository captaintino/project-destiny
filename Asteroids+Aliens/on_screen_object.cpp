#include "on_screen_object.h"
#include <QPainter>

on_screen_object::on_screen_object(QWidget *parent, World *get_world, int initlevel, int type, int x, int y):QLabel(parent), this_world(get_world), level(initlevel), levelOver(false)
{

    game_object = this_world->createLameOjbect(type, x, y);
    this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
    setScaledContents(true);
    this->setPixmap(QPixmap(game_object->getType()));
    this->show();
}

on_screen_object::on_screen_object(QWidget *parent, World *get_world, int initlevel, Obstacle *p):QLabel(parent), this_world(get_world), level(initlevel), levelOver(false)
{
    game_object = p;
    this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
    setScaledContents(true);
    QPixmap image = QPixmap(game_object->getType());
    this->setPixmap(image);   
    this->show();
}

void on_screen_object::update()
{
    if(game_object->isAlive)
        this->setShown(true);
    else
        this->setShown(false);
    this->setGeometry(x(), game_object->getY(), width(), height());
    if(this->game_object->getType() == ":/images/user_projectile.png")
    {
        if(y() < 0)
        {
            if(levelOver)
            {
                emit deleteMe();
            } else
            {
                this_world->deleteObject(game_object);
                this->deleteLater();
            }
        }
    }
    else if(y() > 600)
    {
        if(levelOver){
            emit deleteMe();
        }else if (!(game_object->getType() == ":/images/projectile.png"))
        {
            this_world->deleteObject(game_object);
            game_object = this_world->createObject(level);
            this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
            this->setPixmap(game_object->getType());
        }
    }

}

void on_screen_object::setLevelOver()
{
    levelOver = true;
}
