#include "fakewheel.h"
#include "ui_fakewheel.h"
#include "wheelwidget.h"
#include "map.h"

FakeWheel::FakeWheel(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::FakeWheel)
{
    ui->setupUi(this);

    for (auto *box: {ui->rpm_lower, ui->rpm_upper, ui->amps_lower, ui->amps_upper})
        box->setRange(-100, 100);

    m_rpm = new FakeValueDial(ui->rpm_lower, ui->rpm_upper, ui->rpm, this);
    m_rpm->setLow(-30.);
    m_rpm->setHigh(30.);

    m_pos = new FakeValueDial(ui->amps_lower, ui->amps_upper, ui->pos, this);
    m_pos->setLow(-5.);
    m_pos->setHigh(5.);
}

FakeWheel::~FakeWheel()
{
    delete ui;
}

void FakeWheel::triggerDials()
{
    for(auto & dial : {m_pos, m_rpm})
        dial->onDialSet();
}

FakeValueDial *FakeWheel::pos()
{
    return m_pos;
}

FakeValueDial *FakeWheel::rpm()
{
    return m_rpm;
}

int FakeWheel::speed()
{
    return false;
}

int FakeWheel::position()
{
    return m_pos->value();
}

bool FakeWheel::switchState()
{
    return false;
}

void FakeWheel::setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
    // TODO do smth
}

void FakeWheel::setResistance(uint8_t)
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
