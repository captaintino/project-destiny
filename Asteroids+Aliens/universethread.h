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
        void run(){
            timer->start();
        }
        void updateTimer(int level){timer->setInterval(sqrt(1000/level));}
        ~UniverseThread(){timer->deleteLater();}
private slots:
    void updateModel(){theUniverse->move();}
};
#endif // UNIVERSETHREAD_H
