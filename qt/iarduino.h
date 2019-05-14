#ifndef IARDUINO_H
#define IARDUINO_H
#include <QObject>
#include <QtSerialPort/QSerialPort>

class IArduino
{
public:
    virtual int speed()=0;
    virtual int position()=0;
    virtual bool switchState()=0;
    virtual ~IArduino(){}

    virtual void setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b)=0;
    virtual void setResistance(uint8_t)=0;
};
#endif // IARDUINO_H
