#include <QApplication>
#include "wheelwidget.h"
#include "arduinos/fakewheel.h"
#include "arduinos/arduinoserial.h"
#include <QTextStream>
#include <QDebug>
#include "games/igame.h"
#include "games/templerunner.h"
#include "map.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WheelWidget wheelWidget;

    wheelWidget.weightGauge()->setLow(-1024);
    wheelWidget.weightGauge()->setHigh(1024);

    bool fake = false;
    IArduino * arduino =
            (!fake) ? (IArduino*)new ArduinoSerial("/dev/ttyACM0")
                    : (IArduino*)new FakeWheel();


    IGame *games[3] = {
        new TempleRunner(),
        new TempleRunner(Qt::yellow, Qt::magenta),
        new TempleRunner(Qt::cyan, Qt::darkGreen)
    };

    for (IGame *game : games)
    {
        QObject::connect(game, &IGame::setLED,
                         arduino, &IArduino::setLED);
        game->start();
    }

    int oldSwitchState = 0;
    QObject::connect(arduino, &IArduino::onData,
                     [&](int speed, int weight, int switchState, bool reset){
                              std::cout << switchState << std::endl;
                              if (reset || oldSwitchState != switchState)
                              {
                                  games[switchState]->start();
                              }

                              games[switchState]->update(speed, weight, switchState, reset);
                              oldSwitchState = switchState;

                        });




    QObject::connect(arduino, &IArduino::onData,
                     [&](int speed, int weight, int switchState, bool){
                            wheelWidget.weightGauge()->setValue(weight);
                            wheelWidget.rpmGauge()->setValue(map(speed, 0, 1024, -10, 10));
                      });
    wheelWidget.show();
    return app.exec();
}
