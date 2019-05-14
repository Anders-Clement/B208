#include "wheelwidget.h"
#include "ui_wheelwidget.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include "map.h"

class ArcGraphicsItem : public QGraphicsEllipseItem
{
public:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override {
        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawArc(rect(), startAngle(), spanAngle());
    }
};

WheelWidget::WheelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WheelWidget)
{
    ui->setupUi(this);
    graphicsScene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(graphicsScene);

    int x = 100;
    int y = 100;
    auto rect = [&](int radius){
        return QRect(x-radius, y-radius, radius*2, radius*2);
    };

    int startR = 200;
    m_rpmGauge = new RPMGauge(rect(startR), {80, 100}, {64, 224, 208}, graphicsScene, "R");
    m_posGauge = new Gauge(rect(startR + 10), {80, 115}, Qt::green, graphicsScene, "P");

}

WheelWidget::~WheelWidget()
{
    delete ui;
}

Gauge *WheelWidget::posGauge()
{
    return m_posGauge;
}

Gauge *WheelWidget::rpmGauge()
{
    return m_rpmGauge;
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

void RPMGauge::setValue(qreal value)
{
    m_value = value;
    QString text;
    m_text->setText(prefix + QString::number(value, 'g', 4));
}

Gauge::Gauge(QRect gaugeRect, QPoint textPos, QColor color, QGraphicsScene *scene, QString prefix, QObject *parent):
    Gauge(initEllipse(gaugeRect, color, scene), initText(textPos, color, scene), prefix, parent)
{}
Gauge::Gauge(QGraphicsEllipseItem *ellipse, QGraphicsSimpleTextItem *text, QString prefix, QObject *parent):
    QObject(parent), m_ellipse(ellipse), m_text(text), prefix(prefix)
{}
QGraphicsEllipseItem * Gauge::initEllipse(QRect rect, QColor color, QGraphicsScene *scene)
{
    auto ellipse = new ArcGraphicsItem();
    scene->addItem(ellipse);
    QPen pen;
    pen.setWidth(10);
    pen.setColor(color);
    ellipse->setPen(pen);
    ellipse->setRect(rect);
    ellipse->setStartAngle(90*16);
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
