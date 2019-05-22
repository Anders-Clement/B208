#include "arduinoserial.h"
#include <QTextStream>


ArduinoSerial::ArduinoSerial(QSerialPort *port):
    m_port(port)
{
    connect(m_port, &QSerialPort::readyRead, this, &ArduinoSerial::handleReadyRead);
}

ArduinoSerial::ArduinoSerial(const QString &portPath)
{
    QTextStream standardOutput(stdout);

    m_port = new QSerialPort(this);

    m_port->setPortName(portPath);
    const int serialPortBaudRate = QSerialPort::Baud38400;
    m_port->setBaudRate(serialPortBaudRate);

    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_port->open(QIODevice::ReadWrite)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(portPath)
                          .arg(m_port->errorString())
                       << endl;
    }

    connect(m_port, &QSerialPort::readyRead, this, &ArduinoSerial::handleReadyRead);
}

void ArduinoSerial::setLED(int index, int r, int g, int b)
{
    m_port->write(QString("#1,%1,%2,%3,%4,!")
                  .arg(index).arg(r).arg(g).arg(b).toUtf8());
}

void ArduinoSerial::setResistance(int resistance)
{
    m_port->write(QString("#2,%1,!")
                  .arg(resistance).toUtf8());
}

void ArduinoSerial::handleReadyRead()
{
    auto bytes = m_port->readAll();
    buffer.append(bytes);
    auto start = buffer.indexOf('#');
    if (start == -1)
        return;
    auto end = buffer.lastIndexOf("!");
    if (end == -1)
        return;
    auto toParse = buffer.mid(start, end - start);
    buffer = buffer.mid(end + 1);
    for (auto & line : toParse.split('!'))
    {
//        if (!line.endsWith("!"))/*
//            continue;*/
        line.chop(1);
        std::vector<int> ints;
        for (auto & val: line.mid(1, -1).split(','))
            ints.push_back(val.toInt());
        int switchState = 0;
        for (int i = 2; i < 4; ++i)
            if (ints[i])
                break;
            else ++switchState;

        onData(ints[0], ints[1], switchState, false);
    }
}

