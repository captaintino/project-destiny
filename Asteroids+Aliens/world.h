#ifndef WORLD_H
#define WORLD_H

#include<QTimer>
#include<vector>
#include<obstacle.h>
#include<projectile.h>
#include<ship.h>

using namespace std;



class World: public QObject
{
private:
    Q_OBJECT;
    vector<Obstacle *> asteroids;
    vector<Obstacle *> aliens;
    vector<Projectile *> enemyProjectiles;
    vector<Projectile *> projectiles;
    vector<int> lanesToReset;
    bool hasShip;
    bool lanes[13];
    int projectileCountdown;

    Obstacle * objectFactory(int x, int y, int speed, int type);
public:
    World(bool hasAShip);

    ~World();

    Obstacle* createObject(int level);

    Obstacle* createLameOjbect(int type, int x, int y);

    Obstacle* getLastProjectile();

    void collision();

    void move();

    void lameToWalk();

    void deleteObject(Obstacle * object_to_delete);

    void checkUserShip(Ship *playerShip);

    void projectileGenerator();

    // Saves the world state
    string save();

    // Loads the world state
    void load();
private slots:
    void resetLane();

signals:
    void shipCrashed();
    void projectileCreated();
};

#endif // WORLD_H
