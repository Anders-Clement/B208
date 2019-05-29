#ifndef TEMPLERUNNER_H
#define TEMPLERUNNER_H
#include <QObject>
#include <QColor>
#include "igame.h"

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
    explicit TempleRunner(QColor target=Qt::green, QColor obstacle=Qt::red, QObject *parent=nullptr);
    ~TempleRunner() override;
    void start() override;
    void update(int speed, int weight, int switchState, bool reset) override;
private:
    void update(int position);
    QColor m_target;
    QColor m_obstacle;
};

#endif // TEMPLERUNNER_H
