#include "world.h"
#include<asteroid.h>
#include<alien.h>
#include<mainwindow.h>
#include<QTimer>
#include<cmath>
#include<QString>

#define PI 3.14159265

World::World(bool hasAShip):hasShip(hasAShip)
{
    for(int i = 0; i < 13; ++i){
        lanes[i] = true;
    }
}

World::~World()
{
    for(int i = 0; i < objects.size();){
        delete objects.at(i);
        objects.erase(objects.begin());
    }
    for(int i = 0; i < enemyProjectiles.size();){
        delete enemyProjectiles.at(i);
        enemyProjectiles.erase(enemyProjectiles.begin());
    }
    for(int i = 0; i < projectiles.size();){
        delete projectiles.at(i);
        projectiles.erase(projectiles.begin());
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
        obj->setSpeed(8);
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

void World::checkUserShip(Ship * playerShip)
{
    for(int cur = 0; cur < objects.size(); ++cur)
    {
        Obstacle * obj = objects.at(cur);
        double shipRad = playerShip->getW() / 2;
        double shipX = playerShip->getX() + shipRad;
        double shipY = playerShip->getY() + shipRad;

        double objRad = obj->getW() / 2;
        double objX = obj->getX() + objRad;
        double objY = obj->getY() + objRad;

        if(!(((objX - objRad) > (shipX + shipRad)) ||
              ((shipX - shipRad) > (objX + objRad))) &&
                !(((shipY + shipRad) < (objY - objRad)) ||
                  ((objY + objRad) < (shipY - shipRad))))
        {


            //What follows is known as magic. It is what should never have to be done.
            //We'll call it "Simplified Circular Collision Detection" -- it checks octagons.
            if(!(((shipX + (sin(225*PI/180)*shipRad)) > (objX + (sin(135*PI/180) * objRad))) ||
                ((objX + (sin(225 * PI/180)*objRad)) > (shipX + (sin(135*PI/180)*shipRad)))) &&
                !(((shipY + (cos(225*PI/180)*shipRad)) > (objY + (cos(315*PI/180) * objRad))) ||
                ((objY + (sin(225 * PI/180)*objRad)) > (shipY + (cos(315*PI/180) * shipRad)))))
            {

            //if(sqrt(((shipX - objX)*(shipX - objX)) + ((shipY - objY)*(shipY - objY)) < (shipRad + objRad)))
            //{
                playerShip->setHit(true);
                shipCrashed();
            }
        }
    }
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
    return objectFactory(61.5 * lane, -60, 8); // add item to world and return it
}

// Create a non-moving object
Obstacle *World::createLameOjbect()
{
    return objectFactory(61.5 * objects.size(), -60 -(60*(rand()%27)), 0); // This code is designed to be called 13 times
}

// Open up lane for another item to be created in it
void World::resetLane(){
    lanes[lanesToReset.at(0)] = true; // Reopen the lane that has been closed the longest
    lanesToReset.erase(lanesToReset.begin()); // shift vector over
}

// Randomly creates either an alien or an asteroid, places it in the proper vector and returns it
Obstacle *World::objectFactory(int x, int y, int speed)
{
    switch(rand() % 2){
    case 0:
        objects.push_back(new Asteroid(x, y, speed));
        break;
    case 1:
        objects.push_back(new Alien(x, y, speed));
        break;
    }
    return objects.at(objects.size() - 1);
}
