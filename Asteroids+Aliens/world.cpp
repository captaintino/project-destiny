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
    for(int i = 0; i < objects.size(); ++i){
        objects.at(i)->move(); // Move all the asteroids
    }
}

void World::lameToWalk()
{
    for(Obstacle* obj:objects)
    {
        obj->setSpeed(2);
    }
}

void World::deleteObject(Obstacle *object_to_delete)
{
    for(int i = 0; i < objects.size(); ++i)
    {
        if(objects.at(i) == object_to_delete)
        {
            delete object_to_delete;
            objects.erase(objects.begin()+i);
            break;
        }
    }
}

Obstacle* World::createObject(int level)
{
    int lane = (rand() % 13);
    while(!lanes[lane]){
        lane = (rand() % 13);
        qDebug("Checking next lane...");
    }
    lanes[lane] = false;
    qDebug("Found a lane... should be creating soon.");
    QTimer::singleShot(1000/sqrt(level), this, SLOT(resetLane()));
    lanesToReset.push_back(lane);
    qDebug("Connected the slot.");
    objects.push_back(new Asteroid(61.5 * lane, -60));
    return objects.at(objects.size() - 1);
}

Obstacle *World::createLameOjbect()
{
    objects.push_back(new Asteroid(61.5 * objects.size(), -60 -(20*(rand()%27)), 0));
    return objects.at(objects.size() - 1);
}

void World::resetLane(){
    lanes[lanesToReset.at(0)] = true;
    lanesToReset.erase(lanesToReset.begin());
}
