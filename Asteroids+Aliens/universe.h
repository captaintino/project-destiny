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
    int current_dimension, score;
    unsigned short level;
    Ship * player;
    Ship * playerShip;
    bool cheat;
public:
    Universe(int lvl, int i, bool b);

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

    void incrementScore(){score += 50;}

    void checkUserShip();

    void setUserShip(int new_x, int new_y, int width, int height);

    // Getter Methods:
    Ship* getShip();
    int getScore(){return score;}
    int getLevel(){return level;}

signals:
    void shipCrashed();
    void projectileCreated();

private slots:
    void shipCrashedSignal();
    void projectileCreatedSignal();
};

#endif // UNIVERSE_Hl
