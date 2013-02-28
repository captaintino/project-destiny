#include "world.h"
#include<asteroid.h>
#include<mainwindow.h>

World::World(QWidget * host, int worldSpeed, bool hasAShip, Ship *player):hostWindow(host), hasShip(hasAShip), playerShip(player)
{
    for(int i = 0; i < 13; ++i){
        asteroids.push_back(new Asteroid(hostWindow, i * 61.5, -60));
    }

}

void World::move()
{
    for(int i = 0; i < asteroids.size(); ++i){
        asteroids.at(i)->move(); // Move all the asteroids
    }
}
