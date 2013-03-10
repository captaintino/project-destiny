#include "world.h"
#include<asteroid.h>
#include<mainwindow.h>
#include<QTimer>
#include<cmath>
#include<QString>

World::World(bool hasAShip, Ship *player):hasShip(hasAShip), playerShip(player)
{
    for(int i = 0; i < 13; ++i){
        lanes[i] = true;
    }
}

// Move positions of all the items in the world
void World::move()
{
    for(int i = 0; i < objects.size(); ++i){
        objects.at(i)->move(); // Move all the asteroids
    }
}

// Set all objects in the world to moving
void World::lameToWalk()
{
    for(Obstacle* obj:objects)
    {
        obj->setSpeed(10);
    }
}

// Find <object_to_delete> in the world and delete it
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

void World::checkUserShip()
{
    for(int cur = 0; cur < objects.size(); ++cur)
    {
        Obstacle * obj = objects.at(cur);
        if(!((obj->getX() - (playerShip->getX() + playerShip->getW()) > 0) ||
            ((obj->getX() + obj->getW()) - playerShip->getX() < 0)) &&
            !((obj->getY() - (playerShip->getY() + playerShip->getH()) > 0) ||
            ((obj->getY() + obj->getH()) - playerShip->getY() < 0)))
        {
            playerShip->setHit(true);
            shipCrashed();
        }
    }
    // Code below was from an earlier version... some features may need to be implemented from it, so I'm saving it for now. #Konrad
    /*
    bool ship_dead = false;
    for(int cur = 0; cur < objects.size(); ++cur)
    {
        Obstacle * obj = objects.at(cur);
        if(new_x == obj->getX() && new_y == obj->getY())
        {
            ship_dead = true;
        }
    }
    */
    /*
    for(int cur = 0; cur < objects.size(); ++cur)
    {
        Obstacle * obj = objects.at(cur);
        if(!(new_x + playerShip->getR() < obj->getX()))
        {
            if(!(new_x > obj->getX() + obj->getW()))
            {
                for(int i = obj->getX(); i <= obj->getW(); ++i)
                {
                    for(int j = new_x; j <= new_x; ++j)
                    {
                        if(j == i)
                        {
                            ship_dead = true;
                        }
                    }
                }
            }
        }
        if(!(new_y + playerShip->getR() < obj->getY()))
        {
            if(!(new_y > obj->getY() + obj->getH()))
            {
                for(int i = obj->getY(); i <= obj->getY(); ++i)
                {
                    for(int j = new_y; j <= new_y; ++j)
                    {
                        if(j == i)
                        {
                            ship_dead = true;
                        }
                    }
                }
            }
        }
    }

    if(ship_dead == true)
    {
        playerShip->setHit(true);
        shipCrashed();

    }
    */
}

void World::setUserShip(int new_x, int new_y, int width, int height)
{

    playerShip->setCoords(new_x, new_y, width, height);
}

// Create an object in the model and return a pointer to it
Obstacle* World::createObject(int level)
{

    int lane = (rand() % 13); //Pick random lane to place object into
    while(!lanes[lane]){      //Check and repeat until we find a random lane that is clear
        lane = (rand() % 13);
    }
    lanes[lane] = false; // set lane to closed
    QTimer::singleShot(500/sqrt(level), this, SLOT(resetLane())); // Fire off timer that will reopen the lane
    lanesToReset.push_back(lane); // Add an item to the vector for which lane to clear
    objects.push_back(new Asteroid(61.5 * lane, -60)); // add item to world
    return objects.at(objects.size() - 1); // send item back to label
}

// Create a non-moving object
Obstacle *World::createLameOjbect()
{
    objects.push_back(new Asteroid(61.5 * objects.size(), -60 -(60*(rand()%27)), 0)); // This code is designed to be called 13 times
    return objects.at(objects.size() - 1);
}

// Open up lane for another item to be created in it
void World::resetLane(){
    lanes[lanesToReset.at(0)] = true; // Reopen the lane that has been closed the longest
    lanesToReset.erase(lanesToReset.begin()); // shift vector over
}
