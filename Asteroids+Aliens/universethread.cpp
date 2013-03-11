#include "universethread.h"


UniverseThread::UniverseThread(Universe * initUni, int level): QThread(){
    theUniverse = initUni;
    timer = new QTimer(this);
    timer->setInterval(sqrt(1000/level));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateModel()));
}
