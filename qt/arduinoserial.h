#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QTimer>

class ArduinoSerial : public QObject
{
    Q_OBJECT
public:
    ArduinoSerial(QSerialPort *port);

public slots:
    void setLED(int index, int r, int g, int b);
    void setResistance(int);

    void handleReadyRead();
signals:
    void onData(int speed, int weight, int switchState);

private:
    QSerialPort *m_port;
    QByteArray m_readData;
    QTimer m_timer;
    QByteArray buffer;
};

#endif // ARDUINOSERIAL_H
