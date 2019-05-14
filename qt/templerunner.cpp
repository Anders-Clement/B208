#include "templerunner.h"
#include <QTimer>
#include <QObject>
#include "iarduino.h"

TempleRunner::TempleRunner(QObject *parent):
    QObject(parent)
{
//    timer = new QTimer();
//    timer->setInterval(50);
//    QObject::connect(timer, &QTimer::timeout, [this](){ update(); });
//    timer->start();
}


void TempleRunner::start()
{
    GoalsReached = 0;
    GreenPos = 2;
}

void TempleRunner::update(int position)
{
    steps--;
    //If goal is reached, get new step and playerPos:
    playerPos = position;
    if(steps == 0)
    {
        if(playerPos == GreenPos)
        {
            GoalsReached++;
            GreenPos = 1 + rand() * (3-1);  //Random number between 1-3
            steps = 100-GoalsReached;
        }
        else
        {
            start();
        }
    }
    //Light up leds:
    //ledwrite(playerpos, green);
    setLED(playerPos, 0, 255, 0);
    int redPos1;
    int redPos2;
    if(GreenPos == 1)
    {
        redPos1 = 2;
        redPos2 = 3;
    }
    else if (GreenPos == 2)
    {
        redPos1 = 1;
        redPos2 = 3;
    }
    else {
        redPos1 = 1;
        redPos2 = 2;
    }
    //ledwrite(redPos1, 255-steps*red);
    //ledwrite(redPos2, 255-steps*red);
//    int someLed = 0;
    setLED(redPos1, 255-steps, 0, 0);
    setLED(redPos2, 255-steps, 0, 0);
}

TempleRunner::~TempleRunner()
{
}
