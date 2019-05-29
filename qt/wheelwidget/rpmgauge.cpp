#include "rpmgauge.h"
#include <QPen>
#include <QTimer>
#include <QGraphicsScene>

RPMGauge::RPMGauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent):
    Gauge(initEllipse(gaugeRect, color, scene), initText(textPos, color, scene), prefix)
{
    rotateTimer = new QTimer(this);
    rotateTimer->setInterval(frameDelay*1000);
    rotateTimer->callOnTimeout([this]{
        m_ellipse->setRotation(currentRotation += frameDelay * value()/60.*360.);
    });
    rotateTimer->start();
}

QGraphicsEllipseItem * RPMGauge::initEllipse(QRect rect, QColor color, QGraphicsScene *scene)
{
    auto ellipse = new QGraphicsEllipseItem();
    QPen pen;
    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(10);
    pen.setColor(color);
    ellipse->setPen(pen);
    ellipse->setRect(rect);
    scene->addItem(ellipse);
    ellipse->setTransformOriginPoint(ellipse->rect().center());
    return ellipse;
}

void RPMGauge::setValue(qreal value)
{
    m_value = value;
    QString text;
    m_text->setText(prefix + QString::number(value, 'g', 4));
}
