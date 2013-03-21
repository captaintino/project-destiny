#include "world.h"
#include<asteroid.h>
#include<alien.h>
#include<mainwindow.h>
#include<QTimer>
#include<cmath>
#include<QString>
#include "projectile.h"

#define PI 3.14159265

World::World(bool hasAShip):hasShip(hasAShip), projectileCountdown(40)
{
    for(int i = 0; i < 13; ++i){
        lanes[i] = true;
    }
}

World::~World()
{
    for(int i = 0; i < asteroids.size();++i){
        delete asteroids.at(i);
    }
    asteroids.clear();
    for(int i = 0; i < aliens.size(); ++i){
        delete aliens.at(i);
    }
    aliens.clear();
    for(int i = 0; i < enemyProjectiles.size();++i){
        delete enemyProjectiles.at(i);
    }
    enemyProjectiles.clear();
    for(int i = 0; i < projectiles.size();++i){
        delete projectiles.at(i);
    }
    projectiles.clear();
}

// Move positions of all the items in the world
void World::move()
{
    for(int i = 0; i < asteroids.size(); ++i){
        asteroids.at(i)->move(); // Move all the asteroids
    }
    for(int i = 0; i < aliens.size(); ++i){
        aliens.at(i)->move(); // Move all the aliens
    }
    for(int i = 0; i < enemyProjectiles.size(); ++i){
        enemyProjectiles.at(i)->move(); // Move all the projectiles
    }
    projectileGenerator();
}

// Set all objects in the world to moving
void World::lameToWalk()
{
    for(Obstacle* obj:asteroids)
    {
        obj->setSpeed(8);
    }
    for(Obstacle* obj:aliens)
    {
        obj->setSpeed(8);
    }
}

// Find <object_to_delete> in the world and delete it
void World::deleteObject(Obstacle *object_to_delete)
{
    for(int i = 0; i < asteroids.size(); ++i)
    {
        if(asteroids.at(i) == object_to_delete)
        {
            delete object_to_delete;
            asteroids.erase(asteroids.begin()+i);
            return;
        }
    }
    for(int i = 0; i < aliens.size(); ++i)
    {
        if(aliens.at(i) == object_to_delete)
        {
            delete object_to_delete;
            aliens.erase(aliens.begin()+i);
            return;
        }
    }
}

void World::checkUserShip(Ship * playerShip)
{
    for(int cur = 0; cur < asteroids.size(); ++cur)
    {
        Obstacle * obj = asteroids.at(cur);
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
    for(int cur = 0; cur < aliens.size(); ++cur)
    {
        Obstacle * obj = aliens.at(cur);
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
//=======================================================================================
//Generates projectiles based on a random number countdown between 20 and 40.
void World::projectileGenerator()
{
    --projectileCountdown;
    if(projectileCountdown < 1)
    {
        projectileCountdown = (20 + (rand() % 21));
        if(aliens.size())
        {
            Obstacle * shootingAlien = aliens.at(rand() % aliens.size());
            enemyProjectiles.push_back(new Projectile(shootingAlien->getX() + (shootingAlien->getW() / 2), (shootingAlien->getY() + shootingAlien->getH())));
            projectileCreated();
        }
    }
}
//=======================================================================================
//Returns a pointer to the most recently created projectile
Obstacle * World::getLastProjectile()
{
    return enemyProjectiles.at(enemyProjectiles.size() - 1);
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
    return objectFactory(61.5 * (asteroids.size() + aliens.size()), -60 -(60*(rand()%10)), 0); // This code is designed to be called 13 times
}

// Open up lane for another item to be created in it
void World::resetLane(){
    lanes[lanesToReset.at(0)] = true; // Reopen the lane that has been closed the longest
    lanesToReset.erase(lanesToReset.begin()); // shift vector over
}

// Randomly creates either an alien or an asteroid, places it in the proper vector and returns it
Obstacle *World::objectFactory(int x, int y, int speed)
{
    //if(level > 5){
        int chooser = rand() % 2;
    //}
    //else{
    //    int chooser = 0;
    //}
    switch(chooser){
    case 0:
        asteroids.push_back(new Asteroid(x, y, speed));
        return asteroids.at(asteroids.size() - 1);
        break;
    case 1:
        aliens.push_back(new Alien(x, y, speed));
        return aliens.at(aliens.size() - 1);
        break;
    }
}
