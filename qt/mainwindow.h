#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
class FakeWheel;
}
class WheelWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
private:
    Ui::MainWindow *ui;
    WheelWidget *wheelWidget;
    Ui::FakeWheel *fakeWheel;
    QWidget *fakeW;
};

#endif // MAINWINDOW_H
