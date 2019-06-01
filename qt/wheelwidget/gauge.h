#include <QGraphicsEllipseItem>

#ifndef GAUGE_H
#define GAUGE_H

class ArcGraphicsItem : public QGraphicsEllipseItem
{
    /* this class just like QGraphicsEllipseItem but with paint method overriden
       The QGraphicsEllipseItem has start angle and span angle, when drawn when 
       start angle and span angle are not completing the full circle, it will 
       draw the arc but also will draw weird lines from the center of the ellipse 
       to the end of the arc, and I didnt like those. So I made this small class. */
public:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    // Qt calls paint method of graphicsItem, so it can draw itself to widget using the provided painter.
};

class Gauge : public QObject
{
    /*
      Each gauge consists of the arc(or the ellipse) on outside and the text in the center.
      There are low and high values which are used to map the value provided to setValue
      to the the spanAngle. Also there is prefix the is written before the value in the text("RPM ", "Weight ")
    */
    Q_OBJECT
public slots:
    virtual void setLow(qreal);
    virtual void setHigh(qreal);
    virtual void setValue(qreal);
public:
    qreal low() const;
    qreal high() const;
    qreal value() const;

    explicit Gauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent=nullptr);
    explicit Gauge(QGraphicsEllipseItem *ellipse=nullptr, QGraphicsSimpleTextItem *text=nullptr, QString prefix="", QObject *parent=nullptr);
protected:
    static QGraphicsEllipseItem *initEllipse(QRect rect, QColor color, QGraphicsScene *scene);
    static QGraphicsSimpleTextItem *initText(QPoint pos, QColor color, QGraphicsScene *scene);

    QGraphicsEllipseItem *m_ellipse; // aka the arc
    QGraphicsSimpleTextItem *m_text;
    QString prefix;
    qreal m_low=0., m_high=0., m_value=0.;
};

#endif /* !GAUGE_H */
