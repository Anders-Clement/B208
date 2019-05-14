#ifndef TEMPLERUNNER_H
#define TEMPLERUNNER_H

#include "templerunner_global.h"
#include <QTimer>


class TEMPLERUNNERSHARED_EXPORT TempleRunner
{
    int playerPos;
    int GreenPos;
    int steps;
    int GoalsReached;
    QTimer *timer;

    public:
        TempleRunner();
        ~TempleRunner();
        void start();
        void reset();
        void update();
};

#endif // TEMPLERUNNER_H
