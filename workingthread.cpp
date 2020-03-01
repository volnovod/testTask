#include "workingthread.h"
#include <QtMath>
#include <QSettings>
#include <QDir>
#include <QDebug>


WorkingThread::WorkingThread(QObject *parent) : QThread(parent)
{
    deltaT = 100;
    m_X = 0.0;
    deltaX = 0.1;
    m_stop = false;
    m_resume = false;
    m_pause = false;

    loadSettings();
}

WorkingThread::~WorkingThread()
{
    stop();
    wait();
    saveSettings();
}

void WorkingThread::stop()
{
    mutex.lock();
    m_stop = true;
    mutex.unlock();
    condition.wakeOne();
}

void WorkingThread::pause()
{
    mutex.lock();
    m_pause = true;
    mutex.unlock();
    condition.wakeOne();
}

void WorkingThread::resume()
{
    mutex.lock();
    m_pause = false;
    mutex.unlock();
    condition.wakeOne();
}

void WorkingThread::run()
{
    while (!m_stop) {
        mutex.lock();

        if(m_pause){
            condition.wait(&mutex);
        }

        double X = m_X;
        double res = qSin(X);

        emit sendValues(m_X, res);
        m_X += deltaX;

        mutex.unlock();
        msleep(deltaT);
    }
}

void WorkingThread::loadSettings()
{
    QSettings settings(QDir::currentPath() + "/settings", QSettings::NativeFormat);
    settings.beginGroup("AppSettings");
    m_X = settings.value("LastX", 0.0).toFloat();
    settings.endGroup();
}

void WorkingThread::saveSettings()
{
    QSettings settings(QDir::currentPath() + "/settings", QSettings::NativeFormat);
    settings.beginGroup("AppSettings");
    settings.setValue("LastX", m_X);
    settings.endGroup();
}

quint16 WorkingThread::getDeltaT() const
{
    return deltaT;
}

void WorkingThread::setDeltaT(const quint16 &value)
{
    mutex.lock();
    deltaT = value;
    mutex.unlock();
}

float WorkingThread::getDeltaX() const
{
    return deltaX;
}

void WorkingThread::setDeltaX(float value)
{
    mutex.lock();
    deltaX = value;
    mutex.unlock();
}


