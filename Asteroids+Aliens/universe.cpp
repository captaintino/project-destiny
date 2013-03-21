#include "universe.h"
#include<cmath>
#include<mainwindow.h>
#include<fstream>
#include<sstream>

Universe::Universe(int lvl, bool b): level(lvl), cheat(b)
{
    score = 0;
    player = new Ship();
    dimensions.push_back(new World(true));
    connect(dimensions.at(0), SIGNAL(shipCrashed()), this, SLOT(shipCrashedSignal()));
    connect(dimensions.at(0), SIGNAL(projectileCreated()), this, SLOT(projectileCreatedSignal()));
    current_dimension = 0;
}

Universe::~Universe()
{
    for(int i = 0; i<dimensions.size();){
        delete dimensions.at(i);
        dimensions.erase(dimensions.begin());
    }
    delete player;
}

void Universe::move()
{
    player->updateCoords();
    for(int i=0; i<dimensions.size(); ++i)
    {
        if (!cheat) {
            dimensions.at(i)->checkUserShip(player);
        }
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

    for (int i = 0; i < dimensions.size(); ++i) {
        World *w = dimensions.at(i);
        output += w->save();
    }

}

void Universe::clearWorlds()
{
    for(int i = 0; i < dimensions.size();){
        delete dimensions.at(i);
        dimensions.erase(dimensions.begin());
    }
}

void Universe::createWorlds()
{
    dimensions.push_back(new World(true));
    connect(dimensions.at(0), SIGNAL(shipCrashed()), this, SLOT(shipCrashedSignal()));
    connect(dimensions.at(0), SIGNAL(projectileCreated()), this, SLOT(projectileCreatedSignal()));
}

void Universe::setUserShip(int new_x, int new_y, int width, int height)
{
    player->setCoords(new_x, new_y, width, height);
}

Ship *Universe::getShip()
{
    return player;
}

void Universe::shipCrashedSignal(){
    shipCrashed();
}

void Universe::projectileCreatedSignal()
{
    projectileCreated();
}
