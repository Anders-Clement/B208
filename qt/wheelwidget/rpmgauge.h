#include "gauge.h"

#ifndef RPMGAUGE_H
#define RPMGAUGE_H

class RPMGauge : public Gauge
{
    Q_OBJECT
public:
    explicit RPMGauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent=nullptr);

    void setValue(qreal) override;
private:
    static QGraphicsEllipseItem *initEllipse(QRect rect, QColor color, QGraphicsScene *scene);
    qreal frameDelay = 0.016;
    qreal currentRotation;
    QTimer *rotateTimer;
};

#endif /* !RPMGAUGE_H */
