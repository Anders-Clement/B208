#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>
#include "ui_fakewheel.h"
#include "wheelwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fakeWheel(new Ui::FakeWheel),
    fakeW(new QWidget)
{
    ui->setupUi(this);
    fakeWheel->setupUi(fakeW);
    fakeW->show();

    wheelWidget = new WheelWidget();
    wheelWidget->show();


    connect(fakeWheel->rpm, SIGNAL(valueChanged(qreal)),
            wheelWidget, SLOT(setRPM(qreal)));

    connect(fakeWheel->amps, SIGNAL(valueChanged(qreal)),
            wheelWidget, SLOT(setAmps(qreal)));

    connect(fakeWheel->watts, SIGNAL(valueChanged(qreal)),
            wheelWidget, SLOT(setWatts(qreal)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fakeWheel;
    delete wheelWidget;
}
