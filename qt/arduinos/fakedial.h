#ifndef FAKEDIAL_H
#define FAKEDIAL_H

#include <QObject>
#include <QDoubleSpinBox>
#include <QDial>

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
#endif // FAKEDIAL_H
