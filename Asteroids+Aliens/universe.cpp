#include "universe.h"
#include<cmath>
#include<mainwindow.h>

Universe::Universe(int lvl): level(lvl)
{
    Ship * playerShip = new Ship();
    dimensions.push_back(new World(true, playerShip));
    dimensions.at(0);
    worldMove.start(sqrt(1000/lvl));
    QObject::connect(&worldMove, SIGNAL(timeout()), this, SLOT(update_worlds()));
}

void Universe::move()
{
    dimensions.at(0)->move();
}

void Universe::update_worlds()
{

}

// Loads game state from file
void Universe::load(string filename)
{

}

// Saves game state to file
void Universe::save()
{

}
