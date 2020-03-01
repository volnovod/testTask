#pragma once
#include <QWidget>

class QRcodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QRcodeWidget(QWidget *parent = nullptr);
    void setQRData(const float x, const float y);

private:
    QString data;

protected:
    void paintEvent(QPaintEvent *);

};
