#include "rpmgauge.h"
#include <QPen>
#include <QTimer>
#include <QGraphicsScene>

RPMGauge::RPMGauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent):
    Gauge(initEllipse(gaugeRect, color, scene), initText(textPos, color, scene), prefix)
{
    rotateTimer = new QTimer(this);
    rotateTimer->setInterval(frameDelay*1000);
    // this method accepts time in millisecons, so I multiply my float of secs by 1000
    rotateTimer->callOnTimeout([this]{
        /*increment currentRotation based on rpm aka value() and frameDelay
         then call the setRotation with the new rotation on the same line
         the same as:
           currentRotation += frameDelay * value()/60.*360.;
           m_ellipse->setRotation(currentRotation);
         += operator evaluates to the reference of the left operand, so you can write it on one line.
         this function will be called by rotateTimer every frameDelay seconds
         So in 0.016 which is rouglhy 1/60th of the second.
         In the end you get somewhat smooth animation of rotating wheel running at 60fps
         about the math, 360 has something to do with 360 degrees in the circle
         and 60 has something to do with 60 seconds in one minute
         value()/60. aka rpm/60., you get rps(revolutions per second)
         rps*360. cuz one full revolute is 360 degrees
         Then it is multipled by frameDelay, I need to increment the rotation by
         fraction of the second evertime. */
        m_ellipse->setRotation(currentRotation += frameDelay * value()/60.*360.);
    });
    rotateTimer->start();
    // Stater the function passed to callOnTimeout
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
    // Qt will rotate the ellipse around its upper left corner
    // by default, but you can change to the center like this.
    return ellipse;
}

void RPMGauge::setValue(qreal value)
{
    m_value = value;
    QString text; // This line should probably be removed but it's too late I guess.
    m_text->setText(prefix + QString::number(value, 'g', 4));
    // QString::number converts the long value to string
    // 'g' is the format see https://doc.qt.io/qt-5/qstring.html#argument-formats
    // the 4 is the precision, aka how many digits to display after commma
}
