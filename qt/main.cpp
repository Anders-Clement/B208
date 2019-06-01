#include <QApplication>
#include "wheelwidget/wheelwidget.h"
#include "arduinos/arduinoserial.h"
#include "games/templerunner.h"
#include "map.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WheelWidget wheelWidget;

    wheelWidget.weightGauge()->setLow(-1024);
    wheelWidget.weightGauge()->setHigh(1024);

    IArduino * arduino = new ArduinoSerial("/dev/ttyACM0");


    IGame *games[3] = {
        new TempleRunner(),
        new TempleRunner(Qt::yellow, Qt::magenta),
        new TempleRunner(Qt::cyan, Qt::darkGreen)
    }; // The array of games, which are all TempleRunnner but with different colors.

    for (IGame *game : games)
    {
        // Connecting the signals of games to the slots of arduino.
        QObject::connect(game, &IGame::setLED, // signal
                         arduino, &IArduino::setLED); // slot
        QObject::connect(game, &IGame::setResistance,
                         arduino, &IArduino::setResistance);
        game->start();
    }

    int oldSwitchState = 0;
    QObject::connect(arduino, &IArduino::onData,
                     [&oldSwitchState, &games](int speed, int weight, int switchState, bool reset){
                        // This function everytime is run onData is emited by IArduino
                        // ArduinoSerial will emit onData everytime it prse the message.
                              if (reset || oldSwitchState != switchState)
                              {
                                  games[switchState]->start();
                              }

                              games[switchState]->update(speed, weight, switchState, reset);
                              oldSwitchState = switchState;

                        });




    QObject::connect(arduino, &IArduino::onData,
                     [&](int speed, int weight, int switchState, bool){
                         // This function is run at the same time as the previous function
                         // It just updates the UI with new values from onData
                            wheelWidget.weightGauge()->setValue(weight);
                            wheelWidget.rpmGauge()->setValue(map(speed, 0, 1024, -10, 10));
                      });
    wheelWidget.show();
    return app.exec();
}
