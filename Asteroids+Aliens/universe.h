#ifndef UNIVERSE_H
#define UNIVERSE_H
#include<QTimer>
#include<vector>
#include<world.h>

using namespace std;

class Universe
{
private:
    QTimer clock;
    vector<World *> dimensions;
    unsigned char level;
public:
    Universe(char lvl);
};

#endif // UNIVERSE_H
