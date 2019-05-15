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
    GreenPos = rand() % 3 + 1;
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

            if(position+1 == GreenPos) // Still alive, set new obstacle position:
            {
                stepsToObstacle = start_steps  - GoalsReached;
                GreenPos = rand() % 3 + 1;
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
        for(int i = 1; i < 4; i++)
        {
            if(i != GreenPos)
                setLED(i, 255 - stepsToObstacle, 0,0);
            else
                setLED(i, 0,255,0);
        }



        /*
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
                std::cout << "Goals reached: " << GoalsReached << ", steps: " << steps << "GreenPos: " << GreenPos << std::endl;
            }
            else
            {
                start();
            }
        }
        //Light up leds:
        //ledwrite(playerpos, green);
        setLED(GreenPos, 0, 255, 0);

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
        setLED(redPos1, 255-steps, 0, 0);
        setLED(redPos2, 255-steps, 0, 0);
        */
    }
    else {
        setLED(1, 200,200,200);
        setLED(2, 200,200,200);
        setLED(3, 200,200,200);
    }
}

TempleRunner::~TempleRunner()
{
}
