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
    Q_OBJECT
    vector<Obstacle *> asteroids;
    vector<Obstacle *> aliens;
    vector<Obstacle *> waiting;
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

    Obstacle* getUserProjectile();

    void collision();

    void move();

    void lameToWalk();

    void deleteObject(Obstacle * object_to_delete);

    void checkProjectile();

    void checkUserShip(Ship *playerShip);

    void userFires(Ship *playerShip);

    void projectileGenerator();

    void setHasShip(bool newState){hasShip = newState;}

    // Saves the world state
    string save();

    // Loads the world state
    void load();
private slots:
    void resetLane();
    void lameWalker();

signals:
    void shipCrashed();
    void userShot();
    void projectileCreated();
    void alienKilled();
};

#endif // WORLD_H
