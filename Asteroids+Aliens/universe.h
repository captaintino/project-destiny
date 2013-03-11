#ifndef UNIVERSE_H
#define UNIVERSE_H
#include<QTimer>
#include<vector>
#include<world.h>
#include<QObject>

using namespace std;

class Universe: public QObject
{    
private:
    Q_OBJECT
    vector<World *> dimensions;
    int current_dimension;
    unsigned short level;
    Ship * player;
    Ship * playerShip;
public:
    Universe(int lvl);

    ~Universe();

    World * getWorld(int w){return dimensions.at(w);}

    // Moves all the objects in the game
    void move();

    // Loads game state from file
    void load(string filename);

    // Saves game state to file
    void save();

    // Deletes the worlds
    void clearWorlds();

    // Creates a new set of empty worlds
    void createWorlds();

    // sets the level
    void setLevel(int lvl){level = lvl;}

    void checkUserShip();

    void setUserShip(int new_x, int new_y, int width, int height);

    Ship* getShip();

signals:
    void shipCrashed();

private slots:
    void shipCrashedSignal();
};

#endif // UNIVERSE_Hl
