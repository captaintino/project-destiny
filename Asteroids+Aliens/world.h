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
    vector<Obstacle *> objects;
    vector<Projectile *> enemyProjectiles;
    vector<Projectile *> projectiles;
    vector<int> lanesToReset;
    bool hasShip;
    bool lanes[13];
public:
    World(bool hasAShip);

    ~World();

    Obstacle* createObject(int level);

    Obstacle* createLameOjbect();

    void collision();

    void move();

    void lameToWalk();

    void deleteObject(Obstacle * object_to_delete);

    void checkUserShip(Ship *playerShip);

    void setUserShip(int new_x, int new_y, int width, int height);

    Ship* getShip();

    // Saves the world state
    string save();

    // Loads the world state
    void load();
private slots:
    void resetLane();

signals:
    void shipCrashed();
};

#endif // WORLD_H
