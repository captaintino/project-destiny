#include "universe.h"
#include<cmath>
#include<mainwindow.h>

Universe::Universe(int lvl): level(lvl)
{
    player = new Ship();
    dimensions.push_back(new World(true));
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
        dimensions.at(i)->checkUserShip(player);
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
}

void Universe::setUserShip(int new_x, int new_y, int width, int height)
{
    player->setCoords(new_x, new_y, width, height);
}

Ship *Universe::getShip()
{
    return player;
}
