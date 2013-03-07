#include "on_screen_object.h"

on_screen_object::on_screen_object(QWidget *parent, World *get_world, int initlevel):QLabel(parent), this_world(get_world), level(initlevel)
{
    game_object = this_world->createLameOjbect();
    this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
    setScaledContents(true);
    this->setPixmap(QPixmap(game_object->getType()));
    this->show();
}

void on_screen_object::update()
{
    this->setGeometry(x(), game_object->getY(), width(), height());
    if(y() > 600)
    {
        this_world->deleteObject(game_object);
        game_object = this_world->createObject(level);
        qDebug("We ran through the delete/replace logic");
        this->setGeometry(game_object->getX(), game_object->getY(), width(), height());

    }

}
