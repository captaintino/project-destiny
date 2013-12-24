#include "universe.h"
#include<cmath>
#include<mainwindow.h>
#include<fstream>
#include<sstream>

Universe::Universe(int lvl, int i, bool b): score(i), cheat(b), level(lvl)
{
    player = new Ship();
    dimensions.push_back(new World(true));
    connect(dimensions.at(0), SIGNAL(shipCrashed()), this, SLOT(shipCrashedSignal()));
    connect(dimensions.at(0), SIGNAL(projectileCreated()), this, SLOT(projectileCreatedSignal()));
    connect(dimensions.at(0), SIGNAL(alienKilled()), this, SLOT(alienScoreSlot()));
    connect(dimensions.at(0), SIGNAL(userShot()), this, SLOT(userFired()));

    current_dimension = 0;
}

Universe::~Universe()
{
    for(unsigned int i = 0; i<dimensions.size();){
        delete dimensions.at(i);
        dimensions.erase(dimensions.begin());
    }
    delete player;
}

void Universe::move()
{
    player->updateCoords();
    for(unsigned int i=0; i<dimensions.size(); ++i)
    {
        if (!cheat) {
            dimensions.at(i)->checkUserShip(player);
        }
        dimensions.at(i)->checkProjectile();
        dimensions.at(i)->move();
    }
}

// Loads game state from file
void Universe::load(string filename)
{

}

// Saves game state to file
void Universe::save()
{
    ofstream outfile("save.txt");

    if (!outfile)
    {
        exit(1);
    }

    string output;

    output = to_string(level) + " ";
    output += to_string(score) + " ";

    output += to_string(player->getX()) + " ";
    output += to_string(player->getY()) + " ";
    output += to_string(dimensions.size()) + " ";

    for (unsigned int i = 0; i < dimensions.size(); ++i) {
        World *w = dimensions.at(i);
        output += w->save();
    }

    outfile << output;

}

void Universe::clearWorlds()
{
    for(unsigned int i = 0; i < dimensions.size();){
        delete dimensions.at(i);
        dimensions.erase(dimensions.begin());
    }
}

void Universe::createWorlds()
{
    for(int i = 0; i < /*NUM-WORLDS*/ 1; ++i){
        dimensions.push_back(new World(false));
        connect(dimensions.at(i), SIGNAL(shipCrashed()), this, SLOT(shipCrashedSignal()));
        connect(dimensions.at(i), SIGNAL(projectileCreated()), this, SLOT(projectileCreatedSignal()));
        connect(dimensions.at(i), SIGNAL(alienKilled()), this, SLOT(alienScoreSlot()));
        connect(dimensions.at(i), SIGNAL(userShot()), this, SLOT(userFired()));
    }
    dimensions.at(0)->setHasShip(true);
}

void Universe::setUserShip(int new_x, int new_y, int width, int height)
{
    player->setCoords(new_x, new_y, width, height);
}

Ship *Universe::getShip()
{
    return player;
}

void Universe::shipCrashedSignal()
{
    shipCrashed();
}

void Universe::projectileCreatedSignal()
{
    projectileCreated();
}

void Universe::alienScoreSlot()
{
    score +=500; // Upped from 25 to 500, more balancing may be required
}

void Universe::userFired()
{
    userFires();
}


