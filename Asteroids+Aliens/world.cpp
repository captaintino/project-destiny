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
        obj->setSpeed(10);
    }
    for(Obstacle* obj:aliens)
    {
        obj->setSpeed(10);
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
//=======================================================================
// checks every user projectile against all enemies in the world.
void World::checkProjectile()
{
    for(int cur = 0; cur < projectiles.size(); ++cur)
    {
        Projectile * proj = projectiles.at(cur);
        if(proj->isAlive)
        {
            double projW = proj->getW() / 2;
            double projH = proj->getH() / 2;
            double projX = proj->getX() + projW;
            double projY = proj->getY() + projH;

            for(Obstacle * alien :aliens)
            {
                if(alien->isAlive)
                {
                    double alienRad = alien->getW() / 2;
                    double alienX = alien->getX() + alienRad;
                    double alienY = alien->getY() + alienRad;

                    if(!(((projX - projW) > (alienX + alienRad)) ||
                         ((alienX - alienRad) > (projX + projW))) &&
                            !(((alienY + alienRad) < (projY - projH)) ||
                              ((projY + projH) < (alienY - alienRad))))
                    {
                        Alien * dead = dynamic_cast<Alien*>(alien);
                        dead->Kill();
                        alienKilled();
                    }
                }
            }
        }
    }
}

//======================================================================

void World::checkUserShip(Ship * playerShip)
{

    for(int cur = 0; cur < asteroids.size(); ++cur)
    {
        double shipRad = playerShip->getW() / 2;
        double shipX = playerShip->getX() + shipRad;
        double shipY = playerShip->getY() + shipRad;

        Obstacle * obj = asteroids.at(cur);
        if(obj->isAlive)
        {
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
                    playerShip->setHit(true);
                    shipCrashed();
                }
            }
        }
    }
    for(int cur = 0; cur < aliens.size(); ++cur)
    {
        double shipRad = playerShip->getW() / 2;
        double shipX = playerShip->getX() + shipRad;
        double shipY = playerShip->getY() + shipRad;

        Obstacle * obj = aliens.at(cur);
        if(obj->isAlive)
        {
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
                    playerShip->setHit(true);
                    shipCrashed();
                }
            }
        }
    }
    for(int cur = 0; cur < enemyProjectiles.size(); ++cur)
    {

        double shipRad = playerShip->getW() / 2;
        double shipX = playerShip->getX() + shipRad;
        double shipY = playerShip->getY() + shipRad;

        Obstacle * obj = enemyProjectiles.at(cur);
        if(obj->isAlive)
        {
            double objW = obj->getW() / 2;
            double objH = obj->getH() / 2;
            double objX = obj->getX() + objW;
            double objY = obj->getY() + objH;

            if(!(((objX - objW) > (shipX + shipRad)) ||
                 ((shipX - shipRad) > (objX + objW))) &&
                    !(((shipY + shipRad) < (objY - objH)) ||
                      ((objY + objH) < (shipY - shipRad))))
            {
                playerShip->setHit(true);
                shipCrashed();
            }
        }
    }
}
//=======================================================================================
// Creates a user projectile at the current playerShip location
void World::userFires(Ship * playerShip)
{
    Projectile * proj = new Projectile(playerShip->getX() + (playerShip->getW() / 2),
                                       playerShip->getY() + (playerShip->getH() / 2));
    projectiles.push_back(proj);

    //emit signal about projectile creation
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
            enemyProjectiles.push_back(new Projectile(shootingAlien->getX() + (shootingAlien->getW() / 2),
                                                      (shootingAlien->getY() + shootingAlien->getH())));
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

string World::save()
{
    string output;
    output = to_string(asteroids.size()) + " ";
    for (int i = 0; i < asteroids.size(); ++i) {
        Asteroid *a = dynamic_cast<Asteroid *>(asteroids.at(i));
        output += to_string(a->getX()) + " " + to_string(a->getY()) + " ";
    }

    output += to_string(aliens.size()) + " ";
    for (int i = 0; i < aliens.size(); ++i) {
        Alien *a = dynamic_cast<Alien *>(aliens.at(i));
        output += to_string(a->getX()) + " " + to_string(a->getY()) + " ";
    }
    output += "\n";

    return output;
}

void World::load()
{
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
    return objectFactory(61.5 * lane, -60, 8, 0); // add item to world and return it
}

// Create a non-moving object
Obstacle *World::createLameOjbect(int type, int x, int y)
{
    if (type == 0) {
        return objectFactory(61.5 * (asteroids.size() + aliens.size()), -60 -(60*(rand()%10)), 0, type); // This code is designed to be called 13 times
    } else {
        return objectFactory(x, y, 0, type);
    }
}

// Open up lane for another item to be created in it
void World::resetLane(){
    lanes[lanesToReset.at(0)] = true; // Reopen the lane that has been closed the longest
    lanesToReset.erase(lanesToReset.begin()); // shift vector over
}

// Randomly creates either an alien or an asteroid, places it in the proper vector and returns it
Obstacle *World::objectFactory(int x, int y, int speed, int type)
{
    int chooser;
    if (type == 0) {
        //if(level > 5){
        chooser = rand() % 2;
    } else {
        chooser = type - 1;
    }
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
