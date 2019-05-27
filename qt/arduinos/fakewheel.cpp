#include "fakewheel.h"
#include "ui_fakewheel.h"
#include "wheelwidget.h"
#include "map.h"
#include"fakedial.h"


FakeWheel::FakeWheel(QObject *parent) :
    IArduino(parent),
    m_widget(new QWidget),
    ui(new Ui::FakeWheel)
{
    ui->setupUi(m_widget);

    leds = {ui->led0, ui->led1, ui->led2, ui->led3, ui->led4, ui->led5, ui->led6, ui->led7, ui->led8};

    for (auto *box: {ui->rpm_lower, ui->rpm_upper, ui->amps_lower, ui->amps_upper})
        box->setRange(-2048, 2048);

    m_rpm = new FakeValueDial(ui->rpm_lower, ui->rpm_upper, ui->rpm, this);
    m_rpm->setLow(0);
    m_rpm->setHigh(1024);

    m_weight = new FakeValueDial(ui->amps_lower, ui->amps_upper, ui->pos, this);
    m_weight->setLow(0);
    m_weight->setHigh(1024);

    m_timer.setInterval(m_delay);
    m_timer.callOnTimeout([this]{
       this->onData(this->m_rpm->value(),
                    this->m_weight->value(),
                    this->ui->switch_slider->value(),
                    this->ui->reset->checkState());
    });

    m_widget->show();
    m_timer.start();
}


void FakeWheel::setLED(int index, int r, int g, int b)
{
    QPalette p;
    p.setColor(QPalette::Background, {r, g, b});
    leds[index]->setAutoFillBackground(true);
    leds[index]->setPalette(p);
}

void FakeWheel::setResistance(int)
{

}

FakeValueDial::FakeValueDial(QDoubleSpinBox *low, QDoubleSpinBox *high, QDial *dial, QObject *parent):
    QObject (parent), m_lowBox(low), m_highBox(high), m_dial(dial)
{
    connect(m_dial, &QDial::valueChanged,
            this, &FakeValueDial::onDialSet);


    connect(m_lowBox, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged),
            this, &FakeValueDial::lowChanged);

    connect(m_highBox, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged),
            this, &FakeValueDial::highChanged);

    for (auto & box : {m_lowBox, m_highBox})
        connect(box, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged),
                this, &FakeValueDial::onDialSet);
}

void FakeValueDial::onDialSet()
{
    this->valueChanged(value());
    lowChanged(m_lowBox->value());
    highChanged(m_highBox->value());
}

qreal FakeValueDial::value()
{
    auto low = m_lowBox->value();
    auto high = m_highBox->value();
    return map(m_dial->value(), m_dial->minimum(), m_dial->maximum(),
                               low, high);
}

void FakeValueDial::setLow(qreal low)
{
    m_lowBox->setValue(low);
}

void FakeValueDial::setHigh(qreal high)
{
    m_highBox->setValue(high);
}
