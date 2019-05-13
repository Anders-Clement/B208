#include "mainwindow.h"
#include <QApplication>
#include "wheelwidget.h"
#include "fakewheel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WheelWidget wheelWidget;
    FakeWheel fakeWheel;


//    QObject::connect(&fakeWheel, &FakeWheel::wattsChanged,
//                     &wheelWidget, &WheelWidget::setWatts);

    struct {FakeValueDial *fake; Gauge *gauge;} toConnect[] = {
        {fakeWheel.amps(), wheelWidget.ampsGauge()}, {fakeWheel.volts(), wheelWidget.voltsGauge()}, {fakeWheel.rpm(), wheelWidget.rpmGauge()}
    };
    for (auto & tc: toConnect)
    {
        QObject::connect(tc.fake, &FakeValueDial::valueChanged,
                         tc.gauge, &Gauge::setValue);

        QObject::connect(tc.fake, &FakeValueDial::lowChanged,
                         tc.gauge, &Gauge::setLow);

        QObject::connect(tc.fake, &FakeValueDial::highChanged,
                         tc.gauge, &Gauge::setHigh);
    }

    fakeWheel.show();
    wheelWidget.show();

    fakeWheel.triggerDials();

    return app.exec();
}
