#include <QApplication>
#include "wheelwidget.h"
#include "fakewheel.h"
#include "arduinoserial.h"
#include <QTextStream>
#include <QDebug>
#include "templerunner.h"
#include "map.h"
#include "igame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WheelWidget wheelWidget;

    wheelWidget.weightGauge()->setLow(-1024);
    wheelWidget.weightGauge()->setHigh(1024);

    bool fake = true;
    IArduino * arduino =
            (!fake) ? (IArduino*)new ArduinoSerial("/dev/ttyACM0")
                    : (IArduino*)new FakeWheel();


    IGame *games[3] = {
        new TempleRunner(),
        new TempleRunner(),
        new TempleRunner()
    };

    for (IGame *game : games)
    {
        QObject::connect(game, &IGame::setLED,
                         arduino, &IArduino::setLED);
        game->start();
    }

    QObject::connect(arduino, &IArduino::onData,
                     [&](int speed, int weight, int switchState, bool reset){
                              if (reset)
                                  games[switchState]->start();
                              games[switchState]->update(speed, weight, switchState, reset);
                      });

    QObject::connect(arduino, &IArduino::onData,
            [&](int speed, int weight, int switchState, bool){
                //standardOutput << speed << " " << weight << " " << switchState << endl;
            });




    QObject::connect(arduino, &IArduino::onData,
                     [&](int speed, int weight, int switchState, bool){
                            wheelWidget.weightGauge()->setValue(weight);
                            wheelWidget.rpmGauge()->setValue(map(speed, 0, 1024, -10, 10));
                      });
    wheelWidget.show();
    return app.exec();
}
