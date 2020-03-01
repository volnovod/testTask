#pragma once
#include <QWidget>

class ViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWidget(QWidget *parent = nullptr);

    void setCoordinates(float x, float y);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:

    float   m_y;
    float   m_x;

};
