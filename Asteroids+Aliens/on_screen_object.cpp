#include "on_screen_object.h"

on_screen_object::on_screen_object(QWidget *parent, World *get_world, int initlevel):QLabel(parent), this_world(get_world), level(initlevel)
{
    game_object = this_world->createAsteroid(level);
    this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
    setScaledContents(true);
    this->setPixmap(QPixmap(game_object->getType()));
    this->show();
}
