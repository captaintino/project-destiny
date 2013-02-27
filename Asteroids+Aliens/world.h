#ifndef WORLD_H
#define WORLD_H

#include<QTimer>
#include<vector>
#include<universe.h>
#include<obstacle.h>

using namespace std;

class World : public Universe
{
private:
    vector<Obstacle *> asteroids;
    vector<Obstacle *> aliens;
    bool hasShip;
    QTimer speed;
public:
    World(int worldSpeed);

    void collision();

    void move();
};

#endif // WORLD_H
