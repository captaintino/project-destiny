#include "universe.h"

Universe::Universe(QWidget * parent, char lvl): window(parent), level(lvl)
{
    Ship * playerShip = new Ship(window);
    dimensions.push_back(new World(window, level, true, playerShip));
    dimensions.at(0);
}
