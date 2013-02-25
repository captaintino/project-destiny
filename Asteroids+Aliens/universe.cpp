#include "universe.h"

Universe::Universe(char lvl)
{
    level = lvl;
    Ship * playerShip = new Ship();
    dimensions.push_back(new World(level, true, playerShip));
    dimensions.at(0);
}
