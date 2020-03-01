#pragma once

#include <QMainWindow>
#include "workingthread.h"
#include "viewwidget.h"
#include "controlwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void pause();
    void resume();
    void stop();


public slots:
    void receiveValues(const float x, const float y);

private slots:
    void on_stopButton_clicked();

    void on_pauseButton_clicked();

    void on_resumeButton_clicked();

    void on_show2Button_clicked();

    void on_show3Button_clicked();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    WorkingThread m_worker;
    ViewWidget m_viewWidget;
    ControlWidget m_controlWidget;
};
