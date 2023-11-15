#include "controller.h"

Controller::Controller()
{
    connect(&m_workerThread, &QThread::started, this, &Controller::onStarted);
    connect(&m_workerThread, &QThread::finished, this, &Controller::onFinished);
}

Controller::~Controller()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void Controller::StartStopCapturing(bool bStart)
{
    if(bStart == CapturingState())
        return;

    if(bStart)
    {
        m_workerThread.start();
    }
    else
    {
        m_workerThread.quit();
    }
}

bool Controller::CapturingState() const
{
    return m_workerThread.isRunning();
}

void Controller::onStarted()
{
    emit CapturingStateChanged(true);
}

void Controller::onFinished()
{
    emit CapturingStateChanged(false);
}