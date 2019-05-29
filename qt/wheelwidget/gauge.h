#include <QGraphicsEllipseItem>

#ifndef GAUGE_H
#define GAUGE_H

class ArcGraphicsItem : public QGraphicsEllipseItem
{
public:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

class Gauge : public QObject
{
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

    QGraphicsEllipseItem *m_ellipse;
    QGraphicsSimpleTextItem *m_text;
    QString prefix;
    qreal m_low=0., m_high=0., m_value=0.;
};

#endif /* !GAUGE_H */
