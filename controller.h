#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DataBase.h"
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT

    QThread m_workerThread;
    DataBase m_dataBase;

public:

    Controller();
    ~Controller();

    void StartStopCapturing(bool start);
    bool CapturingState() const;

signals:

    void CapturingStateChanged(bool started);
    void DataBaseUpdated();

private slots:

    void onCaptureWorkerError(QString err);
    void onStarted();
    void onFinished();
    void onNewScreenshotCaptured(const ScreenShot& shot);

};

#endif // CONTROLLER_H
