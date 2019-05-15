#include "mainwindow.h"
#include <QApplication>
#include "wheelwidget.h"
#include "fakewheel.h"
#include "arduinoserial.h"
#include <QTextStream>
#include <QDebug>
#include "templerunner.h"
#include "map.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WheelWidget wheelWidget;
//    FakeWheel fakeWheel;


//    QObject::connect(&fakeWheel, &FakeWheel::wattsChanged,
//                     &wheelWidget, &WheelWidget::setWatts);

//    struct {FakeValueDial *fake; Gauge *gauge;} toConnect[] = {
//        {fakeWheel.pos(), wheelWidget.posGauge()}, {fakeWheel.rpm(), wheelWidget.rpmGauge()}
//    };
//    for (auto & tc: toConnect)
//    {
//        QObject::connect(tc.fake, &FakeValueDial::valueChanged,
//                         tc.gauge, &Gauge::setValue);

//        QObject::connect(tc.fake, &FakeValueDial::lowChanged,
//                         tc.gauge, &Gauge::setLow);

//        QObject::connect(tc.fake, &FakeValueDial::highChanged,
//                         tc.gauge, &Gauge::setHigh);
//    }

//    fakeWheel.show();
//    wheelWidget.show();

//    fakeWheel.triggerDials();

    wheelWidget.weightGauge()->setLow(-1024);
    wheelWidget.weightGauge()->setHigh(1024);
//    const int argumentCount = QCoreApplication::arguments().size();
    const QStringList argumentList = QCoreApplication::arguments();

    QTextStream standardOutput(stdout);

    QSerialPort serialPort;
    const QString serialPortName = "/dev/ttyACM0";
    serialPort.setPortName(serialPortName);
    const int serialPortBaudRate = QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPort.errorString())
                       << endl;
        return 1;
    }
    ArduinoSerial arduino(&serialPort);
    TempleRunner templeRunner;
//    QObject::connect(&arduino, &ArduinoSerial::onData,
//                     [&](int speed, int weight, int switchState){
//                            auto pos = weight / (1023/3) + 1;
//                            standardOutput << "pos: " << pos << endl;
//                            templeRunner.update(pos);
//                      });

    QObject::connect(&arduino, &ArduinoSerial::onData,
            [&](int speed, int weight, int switchState){
                standardOutput << speed << " " << weight << " " << switchState << endl;
            });



    QObject::connect(&templeRunner, &TempleRunner::setLED,
                     &arduino, &ArduinoSerial::setLED);

    QObject::connect(&arduino, &ArduinoSerial::onData,
                     [&](int speed, int weight, int switchState){
                            wheelWidget.weightGauge()->setValue(weight);
                            wheelWidget.rpmGauge()->setValue(map(speed, 0, 1024, -10, 10));
                      });
    wheelWidget.show();
    return app.exec();
}
