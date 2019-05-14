#ifndef WHEELWIDGET_H
#define WHEELWIDGET_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class WheelWidget;
}

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

class WheelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WheelWidget(QWidget *parent = nullptr);
    ~WheelWidget();

    Gauge *posGauge();
    Gauge *rpmGauge();
private:
    Ui::WheelWidget *ui;
    QGraphicsScene *graphicsScene;
    Gauge *m_posGauge, *m_rpmGauge;
};

#endif // WHEELWIDGET_H
