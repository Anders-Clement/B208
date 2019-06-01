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
    // setting up the serial port
    m_port = new QSerialPort(this);

    m_port->setPortName(portPath);
    const int serialPortBaudRate = QSerialPort::Baud38400;
    m_port->setBaudRate(serialPortBaudRate); // the baud rate

    // the other stuff which I dont actually understand
    // I think maybe Hans knows what that means.
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    // Try open the port, if it didn't print the error
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
    // writes the command to the serial port
    // .arg calls replace the % placeholders from the string one by one
    // .toUtf8() somehow converts QString to QByteArray, so it can be accepted by write
    m_port->write(QString("#1,%1,%2,%3,%4,!")
                  .arg(index).arg(r).arg(g).arg(b).toUtf8());
}

void ArduinoSerial::setResistance(int resistance)
{
    // anlogue to setLED
    m_port->write(QString("#2,%1,!")
                  .arg(resistance).toUtf8());
}

void ArduinoSerial::handleReadyRead()
{
    // This method everytime there is data to read on the QSerialPort
    auto bytes = m_port->readAll();
    /*
     s - the start of the message from above
     e - the end of the message from above
     - - the middle of the message
     The bytes can be equal to
      A) "#123,32,1,0,0,1,!"
          s---------------e
      B) "#123,32,1,0,0,1,!#123,32,1,0,0,1,!#123,32,1,0,0,1,!"
          s---------------es---------------es---------------e    
      C) "1,1!#123,32,1,0,0,1,!#123,32,1,0,0,1,!#123,32,1,0,0,1,!#12,"
          ---es---------------es---------------es---------------es---
      D) "23,1,0,0,1,!#1"
          -----------es-
        In case  A we got one full message
        In case B we got 3 full messages
        case C begins somehere in the middle of the previous message and ends in the middle
        of the next message
        case D is similar to C, and it is actually subsequent to case C
        So it ends the message begun in C and begins another message

        How to implement the serial communication that parses all the messages?
     */
    buffer.append(bytes);
    /* We have the buffer of not yet parsed bytes from the previous call
       the buffer can be empty or "s-" where '-' is the middle of the message of arbitrary length
       's', 'e' are the start and end of the message accordingly
       if buffer is "s-" then the bytes can be "-es-", "-es", "-e" + "s-e"*n
       "s-e"*n means there can be n of complete messages in buffer.
       In all cases mentioned after appending bytes to buffer
       the buffer should look like ("s-e" * n) + stuff
          where stuff = "s-" and is optional
        wee need to find the start of the leftmost message */ 
    auto start = buffer.indexOf('#');
    if (start == -1)
        return;
        // The end of the rightmost message
    auto end = buffer.lastIndexOf("!");
    if (end == -1)
        return;
    /* And parse all the message(s) in between.
       However bytes can be equal to "-" too in that case we won't find the start or end
       we will just return, hoping the next call will complete the appended bytes*/
    auto toParse = buffer.mid(start, end - start);

    // We are also gonna remove the part we are about to parse from the buffer.
    buffer = buffer.mid(end + 1); // mid returs the substring from the bufer, starting with end + 1
    for (auto & line : toParse.split('!'))
    {
        // .split("!") will turn "s-es-es-e" into array {"s-", "s-", "s-"}, which we can iterate over
        line.chop(1); // chops off the trailing coma
        std::vector<int> ints;
        for (auto & val: line.mid(1, -1).split(',')) // "#10,11,1".mid(1, -1) == "10,11,1" then "10,11,1".split(",") == {"10", "11", "1"}
            ints.push_back(val.toInt());
        // turn three bool into switchState, which is equal to 0,1,2
        int switchState = 0;
        for (int i = 2; i < 4; ++i)
            if (ints[i])
                break;
            else ++switchState;
        // Emit the signal with parsed data.
        onData(ints[0], ints[1], switchState, ints.back());
    }
}

