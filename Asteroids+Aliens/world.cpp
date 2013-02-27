#include "world.h"

World::World(int worldSpeed, bool hasAShip, Ship *player):hasShip(hasAShip), playerShip(player)
{
    speed.setInterval(worldSpeed);
    speed.start();
}
