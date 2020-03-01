#include "viewwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    m_x = 0.0;
    m_y = 0.0;
}

void ViewWidget::setCoordinates(float x, float y)
{
    m_x = x;
    m_y = y;
    if(isVisible()){
        update();
    }
}

void ViewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawLine(0, painter.window().height()/2, painter.window().width(), painter.window().height()/2);

    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));

    quint16 width = painter.window().width();

    if(m_x > width){
        float x = m_x - width;
        painter.drawEllipse(x, painter.window().height()/2, 50, m_y*50);

    }else{
        painter.drawEllipse(m_x, painter.window().height()/2, 50, m_y*50);
    }



    QWidget::paintEvent(event);
}

