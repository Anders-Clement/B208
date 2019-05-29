#include "wheelwidget.h"
#include "ui_wheelwidget.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QColor>
#include "map.h"
#include "rpmgauge.h"
#include "gauge.h"


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
    m_rpmGauge = new RPMGauge(rect(startR), {80, 100}, {64, 224, 208}, graphicsScene, "RPM    ");
    m_weightGauge = new Gauge(rect(startR + 10), {80, 115}, Qt::green, graphicsScene, "Weight ");

}

WheelWidget::~WheelWidget()
{
    delete ui;
}

Gauge *WheelWidget::weightGauge()
{
    return m_weightGauge;
}

Gauge *WheelWidget::rpmGauge()
{
    return m_rpmGauge;
}
