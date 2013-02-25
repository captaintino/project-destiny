#ifndef PROJECTILE_H
#define PROJECTILE_H
#include<QLabel>

class Projectile : public QLabel
{
public:
    Projectile();

    void move();
};

#endif // PROJECTILE_H
