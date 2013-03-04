#include "on_screen_object.h"

on_screen_object::on_screen_object(QWidget *parent, World *get_world):QLabel(parent), this_world(get_world)
{
    game_object = this_world->createAsteroid();
    this->setGeometry(game_object->getX(), game_object->getY(), game_object->getW(), game_object->getH());
    setScaledContents(true);
    this->setPixmap(QPixmap(game_object->getType()));

    this->show();
}
