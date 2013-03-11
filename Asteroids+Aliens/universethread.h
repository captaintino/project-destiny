#ifndef UNIVERSETHREAD_H
#define UNIVERSETHREAD_H
#include<QThread>
#include<universe.h>

class UniverseThread: public QThread
{
    Universe * theUniverse;
    QTimer * timer;
    Q_OBJECT
public:
    explicit UniverseThread(Universe * initUni, int level);

    // Gets called when you call .start on the thread
    void run(){
            timer->start();
        }

    // Updates the timer's interval to be what it should be based on the current <level>
    void updateTimer(int level){timer->setInterval(sqrt(1000/level));}

private slots:
    void updateModel(){theUniverse->move();}
};
#endif // UNIVERSETHREAD_H
