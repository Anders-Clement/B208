#include "fakewheel.h"
#include "ui_fakewheel.h"
#include "wheelwidget.h"
#include "map.h"

FakeWheel::FakeWheel(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::FakeWheel)
{
    ui->setupUi(this);

    for (auto *box: {ui->rpm_lower, ui->rpm_upper, ui->volts_lower, ui->volts_upper, ui->amps_lower, ui->amps_upper})
        box->setRange(-100, 100);

    m_rpm = new FakeValueDial(ui->rpm_lower, ui->rpm_upper, ui->rpm, this);
    m_rpm->setLow(-30.);
    m_rpm->setHigh(30.);

    m_amps = new FakeValueDial(ui->amps_lower, ui->amps_upper, ui->amps, this);
    m_amps->setLow(-5.);
    m_amps->setHigh(5.);

    m_volts = new FakeValueDial(ui->volts_lower, ui->volts_upper, ui->volts, this);
    m_volts->setLow(-5.);
    m_volts->setHigh(5.);
}

FakeWheel::~FakeWheel()
{
    delete ui;
}

void FakeWheel::triggerDials()
{
    for(auto & dial : {m_volts, m_amps, m_rpm})
        dial->onDialSet();
}

FakeValueDial *FakeWheel::amps()
{
    return m_amps;
}

FakeValueDial *FakeWheel::volts()
{
    return m_volts;
}

FakeValueDial *FakeWheel::rpm()
{
    return m_rpm;
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
    auto low = m_lowBox->value();
    auto high = m_highBox->value();
    this->valueChanged(map(m_dial->value(), m_dial->minimum(), m_dial->maximum(),
                           low, high));
    lowChanged(low);
    highChanged(high);
}

void FakeValueDial::setLow(qreal low)
{
    m_lowBox->setValue(low);
}

void FakeValueDial::setHigh(qreal high)
{
    m_highBox->setValue(high);
}
