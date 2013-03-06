#include "world.h"
#include<asteroid.h>
#include<mainwindow.h>
#include<QTimer>
#include<cmath>

World::World(bool hasAShip, Ship *player):hasShip(hasAShip), playerShip(player)
{
    for(int i = 0; i < 13; ++i){
        lanes[i] = true;
    }
}

void World::move()
{
    for(int i = 0; i < asteroids.size(); ++i){
        asteroids.at(i)->move(); // Move all the asteroids
    }
}

void World::lameToWalk()
{
    for(Obstacle* obj:asteroids)
    {
        obj->setSpeed(2);
    }
}

Obstacle* World::createAsteroid(int level)
{
    int lane = (rand() % 13);
    while(!lanes[lane]){
        lane = (rand() % 13);
    }
    lanes[lane] = false;
    QTimer::singleShot(1000/sqrt(level), this, SLOT(resetLane()));
    lanesToReset.push_back(lane);
    return new Asteroid(61.5 * lane, -60);
}

Obstacle *World::createLameAsteroid()
{
    asteroids.push_back(new Asteroid(61.5 * asteroids.size(), -60 -(20*(rand()%27)), 0));
    return asteroids.at(asteroids.size() - 1);
}

void World::resetLane(){
    lanes[lanesToReset.at(0)] = true;
    lanesToReset.erase(lanesToReset.begin());
}
