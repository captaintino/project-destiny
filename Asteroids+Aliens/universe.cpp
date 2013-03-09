#include "universe.h"
#include<cmath>
#include<mainwindow.h>

Universe::Universe(int lvl): level(lvl)
{
    player = new Ship();
    dimensions.push_back(new World(true, player));
    worldMove.start(sqrt(1000/lvl)); // This goes away with a thread
    QObject::connect(&worldMove, SIGNAL(timeout()), this, SLOT(update_worlds()));
}

void Universe::move()
{
    dimensions.at(0)->move();
}

void Universe::update_worlds()
{
    for(int i=0; i<dimensions.size(); ++i)
    {
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
    worldMove.stop(); // This disapears if we thread it
    for(int i = 0; i < dimensions.size();){
        delete dimensions.at(i);
        dimensions.erase(dimensions.begin());
    }
}

void Universe::createWorlds()
{
    dimensions.push_back(new World(true, player));
    worldMove.start(sqrt(1000/level)); // This goes away with a thread
}
