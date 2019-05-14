#ifndef FAKEWHEEL_H
#define FAKEWHEEL_H

#include <QWidget>
#include <functional>
#include "iarduino.h"

namespace Ui {
class FakeWheel;
}

class WheelWidget;
class QDoubleSpinBox;
class QDial;

class FakeValueDial : public QObject
{
    Q_OBJECT
public:
    explicit FakeValueDial(QDoubleSpinBox *low, QDoubleSpinBox *high, QDial* dial, QObject *parent=nullptr);

    void onDialSet();
signals:
    void valueChanged(qreal);

    void lowChanged(qreal);
    void highChanged(qreal);
public slots:
    void setLow(qreal);
    void setHigh(qreal);
public:
    qreal value();
private:
    QDoubleSpinBox *m_lowBox, *m_highBox;
    QDial *m_dial;
};


class FakeWheel : public QWidget, public IArduino
{
    Q_OBJECT
public:
    FakeWheel(QWidget *parent=nullptr);

    virtual ~FakeWheel();

    void triggerDials();
    FakeValueDial *pos();
    FakeValueDial *rpm();

public:
    int speed() override;
    int position() override;
    bool switchState() override;

    void setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b) override;
    void setResistance(uint8_t) override;
private:
    Ui::FakeWheel *ui;
    FakeValueDial *m_pos, *m_rpm;
};

#endif // FAKEWHEEL_H
