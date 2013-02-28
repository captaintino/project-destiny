#include "universe.h"
#include<cmath>
#include<mainwindow.h>

Universe::Universe(QWidget * parent, char lvl): window(parent), level(lvl)
{
    Ship * playerShip = new Ship(parent);
    dimensions.push_back(new World(parent, lvl, true, playerShip));
    dimensions.at(0);
    clock.start(1000);
    worldMove.start(sqrt(1000/lvl));
    dynamic_cast<MainWindow *>(parent)->connectWorldTimer(&worldMove);
}

void Universe::move()
{
    dimensions.at(0)->move();
}
