#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "iarduino.h"

class ArduinoSerial : public IArduino
{
    /*
     Implements the serial communication with the prototype
     */
    Q_OBJECT
public:
    ArduinoSerial(QSerialPort *port);
    ArduinoSerial(const QString & portPath);

    void setLED(int index, int r, int g, int b) override;
    void setResistance(int) override;
public slots:
    void handleReadyRead();
private:
    QSerialPort *m_port;
    QTimer m_timer;
    QByteArray buffer;
};

#endif // ARDUINOSERIAL_H
