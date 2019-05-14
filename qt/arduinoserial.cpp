#include "arduinoserial.h"



ArduinoSerial::ArduinoSerial(QSerialPort *port):
    m_port(port)
{
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

        onData(ints[0], ints[1], switchState);
    }
}

