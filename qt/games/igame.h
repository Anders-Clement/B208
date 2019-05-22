#ifndef IGAME_H
#define IGAME_H

#include <QObject>

class IGame : public QObject
{
    Q_OBJECT
public:
    explicit IGame(QObject *parent = nullptr);

signals:
    void setLED(int id, int r, int g, int b);
    void setReistance(int);
public slots:
    virtual void update(int speed, int weight, int switchState, bool reset)=0;
    virtual void start()=0;
};

#endif // IGAME_H
