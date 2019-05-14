#include "templerunner.h"
#include <QTimer>


TempleRunner::TempleRunner()
{
    timer = new QTimer();
    timer->setInterval(50);
    QObject::connect(timer, &QTimer::timeout, [this](){ update(); });
    timer->start();
}


void TempleRunner::start()
{
    GoalsReached = 0;
    GreenPos = 2;
}

void TempleRunner::update()
{
    steps--;
    //If goal is reached, get new step and playerPos:
    if(steps == 0)
    {
        if(playerPos == GreenPos)
        {
            GoalsReached++;
            GreenPos = 1 + rand() * (3-1);  //Random number between 1-3
            steps = 1000-GoalsReached;
        }
        else
        {
            start();
        }
    }
    //Light up leds:
    //ledwrite(playerpos, green);
    if(GreenPos == 1)
    {
        int redPos1 = 2;
        int redPos2 = 3;
    }
    else if (GreenPos == 2)
    {
        int redPos1 = 1;
        int redPos2 = 3;
    }
    else {
        int redPos1 = 1;
        int redPos2 = 2;
    }
    //ledwrite(redPos1, 255-steps*red);
    //ledwrite(redPos2, 255-steps*red);




}

TempleRunner::~TempleRunner()
{
    delete timer;
}
