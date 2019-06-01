#include "gauge.h"
#include "map.h"
#include <QGraphicsScene>
#include <QPainter>

Gauge::Gauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent):
    Gauge(initEllipse(gaugeRect, color, scene), initText(textPos, color, scene), prefix, parent)
{} 
/* 
 Constructor which just invokes another constructor, and forwards some args to to static initXXX methods
  that are listed below.
 */
Gauge::Gauge(QGraphicsEllipseItem *ellipse, QGraphicsSimpleTextItem *text, QString prefix, QObject *parent):
    QObject(parent), m_ellipse(ellipse), m_text(text), prefix(prefix)
{}

qreal Gauge::low() const
{
    return m_low;
}

qreal Gauge::high() const
{
    return m_high;
}

qreal Gauge::value() const
{
    return m_value;
}

QGraphicsEllipseItem * Gauge::initEllipse(QRect rect, QColor color, QGraphicsScene *scene)
{
    /* 
     Some boilerplate code for setting up ArcGraphicsItem
     */
    auto ellipse = new ArcGraphicsItem();
    scene->addItem(ellipse); 
    // In order for graphicsItem to be drawn it needs to be added to the scene
    // which itself is the part of the graphicsView
    QPen pen;
    pen.setWidth(10);
    pen.setColor(color);
    ellipse->setPen(pen);
    ellipse->setRect(rect);
    ellipse->setStartAngle(90*16); 
    // 90 degrees time 16 cuz Qt accepts accepts integer where 16 units is one degree
    return ellipse;
}

QGraphicsSimpleTextItem * Gauge::initText(QPoint pos, QColor color, QGraphicsScene *scene)
{
    auto text = new QGraphicsSimpleTextItem();
    scene->addItem(text);
    QPen textPen;
    text->setPos(pos);
    textPen.setColor(color);
    text->setPen(textPen);
    return text;
}

void Gauge::setLow(qreal low)
{
    m_low = low;
}

void Gauge::setHigh(qreal high)
{
    m_high = high;
}

void Gauge::setValue(qreal value)
{
    m_value = value;
    m_ellipse->setSpanAngle(-map(m_value, m_low, m_high, -360*16, 360*16));
    QString text;
    m_text->setText(prefix + QString::number(value, 'g', 4));
}

void ArcGraphicsItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawArc(rect(), startAngle(), spanAngle());
}
