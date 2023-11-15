#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include <QObject>
#include <QTimer>

class CaptureWorker : public QObject
{
    Q_OBJECT

    QTimer m_timer;

public:
    explicit CaptureWorker(QObject *parent);
    ~CaptureWorker();

public slots:

    void Start();
    void onTimer();

signals:

    void Error(QString err);
    void NewScreenshotCaptured();
};

#endif // CAPTUREWORKER_H
