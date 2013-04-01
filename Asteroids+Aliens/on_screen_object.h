#ifndef ON_SCREEN_OBJECT_H
#define ON_SCREEN_OBJECT_H

#include <obstacle.h>
#include <world.h>
#include <QLabel>


class on_screen_object : public QLabel
{
    Q_OBJECT
private:
    Obstacle *game_object;
    World *this_world;
    int level;
    bool levelOver;
public:
    explicit on_screen_object(QWidget *parent, World *get_world, int initlevel, int type, int x, int y);
    explicit on_screen_object(QWidget *parent, World *get_world, int initlevel, Obstacle * p);

    virtual void update();

    void setLevelOver();
signals:
    void deleteMe();
public slots:
    
};

#endif // ON_SCREEN_OBJECT_H
