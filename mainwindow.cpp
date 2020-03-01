#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_worker, &WorkingThread::sendValues, this, &MainWindow::receiveValues);

    connect(this, &MainWindow::pause, &m_worker, &WorkingThread::pause);
    connect(this, &MainWindow::resume, &m_worker, &WorkingThread::resume);
    connect(this, &MainWindow::stop, &m_worker, &WorkingThread::stop);

    connect(&m_controlWidget, &ControlWidget::deltaTChanged, &m_worker, &WorkingThread::setDeltaT);
    connect(&m_controlWidget, &ControlWidget::deltaXChanged, &m_worker, &WorkingThread::setDeltaX);

    m_controlWidget.setDeltaT(m_worker.getDeltaT());
    m_controlWidget.setDeltaX(m_worker.getDeltaX());

    m_worker.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveValues(const float x, const float y)
{
//    if(m_controlWidget.isVisible()){
        m_controlWidget.setXY(x, y);
//    }

//    if(m_viewWidget.isVisible()){
        m_viewWidget.setCoordinates(x, y);
//    }
}


void MainWindow::on_stopButton_clicked()
{
    emit stop();
}

void MainWindow::on_pauseButton_clicked()
{
    emit pause();
}

void MainWindow::on_resumeButton_clicked()
{
    emit resume();
}

void MainWindow::on_show2Button_clicked()
{
    if(m_viewWidget.isVisible()){
        m_viewWidget.hide();

    }else{
        m_viewWidget.show();
    }
}

void MainWindow::on_show3Button_clicked()
{
    if(m_controlWidget.isVisible()){
        m_controlWidget.hide();
    }else{
        m_controlWidget.show();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_controlWidget.close();
    m_viewWidget.close();
    QMainWindow::closeEvent(event);
}
