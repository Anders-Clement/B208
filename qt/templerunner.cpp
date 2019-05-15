#include "templerunner.h"
#include <QTimer>
#include <QObject>
#include "iarduino.h"
#include <iostream>
#include "time.h"

TempleRunner::TempleRunner(QObject *parent):
    QObject(parent)
{

}


void TempleRunner::start()
{
    srand(time(NULL));
    GoalsReached = 0;
    alive = true;
    stepsToObstacle = start_steps;
    GreenPos = rand() % 3;
}

void TempleRunner::update(int position)
{
    if(alive)
    {
        stepsToObstacle--;
        if(stepsToObstacle <= 0)    // We are at an obstacle, check player pos, and update
        {
            GoalsReached++;
            stepsToObstacle = start_steps  - GoalsReached * 10;

            if(position == GreenPos) // Still alive, set new obstacle position:
            {
                stepsToObstacle = start_steps  - GoalsReached;
                GreenPos = rand() % 3;
            }
            else
            {
                alive = false;
            }
        }
        else
        {
            stepsToObstacle--;
        }

        //Update led's:
        for(int i = 0; i < 3; i++)
        {
            if(i != GreenPos)
                for(int j = 0; j < 3; j++)
                    setLED(i*3 + j, 255 - stepsToObstacle*2, 0,0);
            else
                for(int j = 0; j < 3; j++)
                    setLED(i*3 +j, 0,255,0);
        }
    }
    else {
        for(int i = 0; i < 9; i++)
            setLED(i, 200,200,200);
    }
}

TempleRunner::~TempleRunner()
{
}
