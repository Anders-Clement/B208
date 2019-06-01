#ifndef IARDUINO_H
#define IARDUINO_H
#include <QObject>
#include <QtSerialPort/QSerialPort>

class IArduino : public QObject
{
    /*
    The abstract class to be implemented by ArduinoSerial
    It describes the interface between pc and the prototype
     */
    Q_OBJECT
signals:
    void onData(int speed, int weight, int gameIdx, bool reset);
    // This signal should be emited everytime new message is received.
    // It is emitted from the inside of the class.
public:
    explicit IArduino(QObject *parent=nullptr);

    virtual ~IArduino();
public slots:
    virtual void setLED(int index, int r, int g, int b)=0;
    virtual void setResistance(int)=0;
    // When both of those methods are called,
    // the corresponding command should be sent to the prototype.
};
#endif // IARDUINO_H
