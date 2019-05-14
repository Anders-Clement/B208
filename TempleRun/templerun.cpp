#include "templerun.h"

TempleRun::TempleRun()
{
    timer = new QTimer(this)
}

void TempleRun::start()
{
    alive = true;
    timer->setInterval(50);
    timer->start();
    connect(timer,&QTimer::timeout,[this](){ update(); });
}

void TempleRun::stop()
{
    timer->stop();
}

void TempleRun::update()
{
}
