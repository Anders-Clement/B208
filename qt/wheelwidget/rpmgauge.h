#include "gauge.h"

#ifndef RPMGAUGE_H
#define RPMGAUGE_H

class RPMGauge : public Gauge
{
    /*
     This class tries to reuse some code from Gauge by inheriting from it.
     Instead of mapping the value provided to the setValue to the spanAngle of the arc
     it maps value to rpm of the wheel. It also changes the ellipse from GraphicsARcItem 
     to normal QGraphicsEllipsItem.
     */
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
