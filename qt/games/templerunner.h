#ifndef TEMPLERUNNER_H
#define TEMPLERUNNER_H
#include <QObject>
#include <chrono>
#include "igame.h"

class IArduino;

class TempleRunner : public IGame
{
    Q_OBJECT
    int playerPos;
    int GreenPos, redPos1, redPos2;
    int stepsToObstacle;
    int GoalsReached;
    int start_steps = 100;
    bool alive;
public:
    explicit TempleRunner(QObject *parent=nullptr);
    ~TempleRunner() override;
    void start() override;
    void update(int speed, int weight, int switchState, bool reset) override;
private:
    void update(int position);
};

#endif // TEMPLERUNNER_H
