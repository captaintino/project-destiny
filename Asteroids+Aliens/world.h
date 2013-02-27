#ifndef WORLD_H
#define WORLD_H

#include<QTimer>
#include<vector>
#include<obstacle.h>
#include<projectile.h>
#include<ship.h>

using namespace std;

class World
{
private:
    vector<Obstacle *> asteroids;
    vector<Obstacle *> aliens;
    vector<Projectile *> enemyProjectiles;
    vector<Projectile *> projectiles;
    bool hasShip;
    QTimer speed;
    Ship * playerShip;
public:
    World(int worldSpeed, bool hasAShip, Ship * player);

    void collision();

    void move();
};

#endif // WORLD_H
