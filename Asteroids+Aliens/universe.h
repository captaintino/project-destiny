#ifndef UNIVERSE_H
#define UNIVERSE_H
#include<QTimer>
#include<vector>
#include<world.h>
#include<QObject>

using namespace std;

class Universe
{    
private:
    vector<World *> dimensions;
    unsigned short level;
    Ship * player;
public:
    Universe(int lvl);

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
};

#endif // UNIVERSE_H
