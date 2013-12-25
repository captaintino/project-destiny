#include "universethread.h"

UniverseThread::UniverseThread(Universe * initUni, int level): QThread(){
    theUniverse = initUni;
    timer = new QTimer(this);
    timer->setInterval((2*(sqrt(100/level)))+25);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateModel()));
}

void UniverseThread::terminate(){
    timer->stop();
    //QThread::finished();
}
