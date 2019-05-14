#ifndef TEMPLERUNNER_H
#define TEMPLERUNNER_H
#include <QObject>
#include <chrono>

class IArduino;

class TempleRunner : public QObject
{
    Q_OBJECT
    int playerPos;
    int GreenPos;
    int steps;
    int GoalsReached;
public:
    explicit TempleRunner(QObject *parent=nullptr);
    ~TempleRunner();
    void start();
    void reset();
    void update(int position);
signals:
    void setLED(int index, int r, int g, int b);
    void setReistance(int resistance);
private:
//    IArduino *m_arduino;
};

#endif // TEMPLERUNNER_H
