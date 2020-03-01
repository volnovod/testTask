#include "controlwidget.h"
#include "ui_controlwidget.h"
#include <QIntValidator>
#include <QDoubleValidator>
#include <QDebug>
#include <QThread>

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);

    m_x = 0.0;
    m_y = 0.0;

    m_qrcode.setParent(ui->qrcodeWidget);

}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::setXY(const float x, const float y)
{
    m_x = x;
    m_y = y;
    updateView();
}

void ControlWidget::setDeltaX(const float deltaX)
{
    ui->deltaX->blockSignals(true);
    ui->deltaX->setText(QString::number(deltaX));
    m_deltaX = deltaX;
    ui->deltaX->blockSignals(false);
}

void ControlWidget::setDeltaT(const quint16 deltaT)
{
    ui->deltaT->blockSignals(true);
    ui->deltaT->setText(QString::number(deltaT));
    m_deltaT = deltaT;
    ui->deltaT->blockSignals(false);
}

void ControlWidget::updateView()
{
    QString fullExpression = "sin(" + QString::number(m_x) + ") = " + QString::number(m_y);
    ui->fullExpression->setText(fullExpression);
    m_qrcode.setQRData(m_x, m_y);
    m_qrcode.resize(ui->qrcodeWidget->size());
}

void ControlWidget::on_deltaX_editingFinished()
{
    float res = ui->deltaX->text().toFloat();
    if(res > 0.0 && res <= 2.0){
        m_deltaX = ui->deltaX->text().toFloat();
        emit deltaXChanged(m_deltaX);
    }else{
        ui->deltaX->setText(QString::number(m_deltaX));
    }
}

void ControlWidget::on_deltaT_editingFinished()
{
    quint16 res = ui->deltaT->text().toInt();
    if(res >= 100 && res <= 300){
        m_deltaT = ui->deltaT->text().toInt();
        emit deltaTChanged(m_deltaT);
    }else{
        ui->deltaT->setText(QString::number(m_deltaT));
    }
}
