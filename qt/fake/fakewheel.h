#ifndef FAKEWHEEL_H
#define FAKEWHEEL_H

#include <QWidget>
#include "arduinos/iarduino.h"
#include <QTimer>

namespace Ui {
class FakeWheel;
}
class FakeValueDial;

class FakeWheel : public IArduino
{
    Q_OBJECT
public:
    FakeWheel(QObject *parent=nullptr);
public:
    void setLED(int index, int r, int g, int b) override;
    void setResistance(int) override;

private:
    QWidget *m_widget;
    Ui::FakeWheel *ui;
    FakeValueDial *m_weight, *m_rpm;
    int m_delay = 1000/10;
    QTimer m_timer;
    std::vector<QWidget*> leds;
};

#endif // FAKEWHEEL_H