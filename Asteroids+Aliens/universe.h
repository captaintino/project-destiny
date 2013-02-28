#ifndef UNIVERSE_H
#define UNIVERSE_H
#include<QTimer>
#include<vector>
#include<world.h>

using namespace std;

class Universe
{
private:
    QTimer clock, worldMove;
    vector<World *> dimensions;
    unsigned short level;
    QWidget * window;
public:
    Universe(QWidget * parent, char lvl);

    // Moves all the objects in the game
    void move();

    // Loads game state from file
    void load(string filename);

    // Saves game state to file
    void save();
};

#endif // UNIVERSE_H
