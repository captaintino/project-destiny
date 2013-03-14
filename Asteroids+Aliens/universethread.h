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
            this->setPriority(QThread::TimeCriticalPriority);
            timer->start();
        }

    // Updates the timer's interval to be what it should be based on the current <level>
    void updateTimer(int level){timer->setInterval((2*(sqrt(100/level))) + 25);}

private slots:
    void updateModel(){theUniverse->move();theUniverse->incrementScore();}
};
#endif // UNIVERSETHREAD_H
