#include "universe.h"

Universe::Universe(QWidget * parent, char lvl): window(parent), level(lvl)
{
    Ship * playerShip = new Ship(parent);
    dimensions.push_back(new World(parent, lvl, true, playerShip));
    dimensions.at(0);
    clock.start(1000);
}

void Universe::move()
{
    dimensions.at(0)->move();
}
