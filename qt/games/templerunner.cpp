#include "templerunner.h"
#include <QTimer>
#include <QObject>
#include <iostream>
#include "time.h"

TempleRunner::TempleRunner(QColor target, QColor obstacle, QObject *parent):
    IGame(parent),
    m_target(target),
    m_obstacle(obstacle)
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

void TempleRunner::update(int speed, int weight, int switchState, bool reset)
{
    auto position = weight / (1024/3);
    position = position <= 2 ? position : 2;
    update(position);
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
                {
//                    setLED(i*3 + j, 255 - stepsToObstacle*2, 0,0);
                    auto dim = 255/(255 - stepsToObstacle*2);
                    setLED(i*3 + j, m_obstacle.red()/dim, m_obstacle.green()/dim, m_obstacle.blue()/dim);
                }
            else
                for(int j = 0; j < 3; j++)
                    setLED(i*3 +j, m_target.red(), m_target.green(), m_target.blue());
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
