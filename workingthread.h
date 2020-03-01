#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class WorkingThread : public QThread
{
    Q_OBJECT
public:
    WorkingThread(QObject *parent = nullptr);
    ~WorkingThread();

    float getDeltaX() const;
    quint16 getDeltaT() const;

signals:
    void sendValues(const float x, const float y);
    void sendDeltaX(float deltaX);
    void sendDeltaT(quint16 deltaT);

public slots:
    void stop();
    void pause();
    void resume();
    void setDeltaT(const quint16 &value);
    void setDeltaX(float value);

    // QThread interface
protected:
    void run() override;

private:
    
    void loadSettings();
    void saveSettings();

    QMutex mutex;
    QWaitCondition condition;
    quint16 deltaT;
    float   m_X;
    float   deltaX;
    bool m_stop;
    bool m_pause;
    bool m_resume;
};
