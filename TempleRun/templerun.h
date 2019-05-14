#ifndef TEMPLERUN_H
#define TEMPLERUN_H

#include <QTimer>

class TempleRun
{
int playerPos;
int GreenPos;
int timeToNext;
bool alive;
QTimer *timer;


public:
    TempleRun();
    void start();
    void stop();
    void reset();
    void update();
};

#endif // TEMPLERUN_H
