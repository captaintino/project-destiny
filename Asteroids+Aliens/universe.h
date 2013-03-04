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
    QTimer worldMove;
    vector<World *> dimensions;
    unsigned short level;
public:
    Universe(int lvl);

    // Moves all the objects in the game
    void move();

    // Loads game state from file
    void load(string filename);

    // Saves game state to file
    void save();

private slots:
    void update_worlds();
};

#endif // UNIVERSE_H
