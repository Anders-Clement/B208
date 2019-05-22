#ifndef IARDUINO_H
#define IARDUINO_H
#include <QObject>
#include <QtSerialPort/QSerialPort>

class IArduino : public QObject
{
    Q_OBJECT
signals:
    void onData(int speed, int weight, int gameIdx, bool reset);
public:
    explicit IArduino(QObject *parent=nullptr);

    virtual ~IArduino();
public slots:
    virtual void setLED(int index, int r, int g, int b)=0;
    virtual void setResistance(int)=0;
};
#endif // IARDUINO_H
