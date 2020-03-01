#pragma once
#include <QWidget>
#include "qrcodewidget.h"

namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

    void setXY(const float x, const float y);

    void setDeltaX(const float deltaX);
    void setDeltaT(const quint16 deltaT);

signals:
    void deltaTChanged(const quint16 deltaT);
    void deltaXChanged(const float deltaX);

private slots:
    void on_deltaX_editingFinished();

    void on_deltaT_editingFinished();

private:

    void updateView();

    Ui::ControlWidget *ui;
    float m_x;
    float m_y;
    float m_deltaX;
    quint16 m_deltaT;
    QRcodeWidget m_qrcode;

};
