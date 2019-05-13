#ifndef FAKEWHEEL_H
#define FAKEWHEEL_H

#include <QWidget>
#include <functional>


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
private:
    QDoubleSpinBox *m_lowBox, *m_highBox;
    QDial *m_dial;
};

class FakeWheel : public QWidget
{
    Q_OBJECT
public:
    FakeWheel(QWidget *parent=nullptr);

    virtual ~FakeWheel();

    void triggerDials();
    FakeValueDial *amps();
    FakeValueDial *volts();
    FakeValueDial *rpm();
private:
    Ui::FakeWheel *ui;
    std::vector<std::function<void(void)>> dialSetTriggers;
    FakeValueDial *m_amps, *m_volts, *m_rpm;
};

#endif // FAKEWHEEL_H
