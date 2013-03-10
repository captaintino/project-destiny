#include "world.h"
#include<asteroid.h>
#include<mainwindow.h>
#include<QTimer>
#include<cmath>
#include<QString>

#define PI 3.14159265

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
            double shipRad = playerShip->getW() / 2;
            double shipX = playerShip->getX() + shipRad;
            double shipY = playerShip->getY() + shipRad;

            double objRad = obj->getW() / 2;
            double objX = obj->getX() + objRad;
            double objY = obj->getY() + objRad;

            //What follows is known as magic. It is what should never have to be done.
            //We'll call it "Simplified Circular Collision Detection" -- it checks octagons.
            if(!(((shipX + (sin(225*PI/180)*shipRad)) > (objX + (sin(135*PI/180) * objRad))) ||
                ((objX + (sin(225 * PI/180)*objRad)) > (shipX + (sin(135*PI/180)*shipRad)))) &&
                !(((shipY + (cos(222*PI/180)*shipRad)) > (objY + (sin(135*PI/180) * objRad))) ||
                ((objY + (sin(225 * PI/180)*objRad)) > (shipY + (sin(135*PI/180) * shipRad)))))
            {
                playerShip->setHit(true);
                shipCrashed();
            }
        }
    }

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
