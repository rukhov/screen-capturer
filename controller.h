#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>

class Controller : public QObject
{
    Q_OBJECT

    QThread m_workerThread;

public:

    Controller();
    ~Controller();

    void StartStopCapturing(bool start);
    bool CapturingState() const;

signals:

    void CapturingStateChanged(bool started);

private slots:

    void onStarted();
    void onFinished();

};

#endif // CONTROLLER_H
