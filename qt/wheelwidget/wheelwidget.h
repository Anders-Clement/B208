#ifndef WHEELWIDGET_H
#define WHEELWIDGET_H

#include <QWidget>
#include "gauge.h"

namespace Ui {
class WheelWidget;
}

class WheelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WheelWidget(QWidget *parent = nullptr);
    ~WheelWidget();

    Gauge *weightGauge();
    Gauge *rpmGauge();
private:
    Ui::WheelWidget *ui;
    QGraphicsScene *graphicsScene;
    Gauge *m_weightGauge, *m_rpmGauge;
};

#endif // WHEELWIDGET_H
