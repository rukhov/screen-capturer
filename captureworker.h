#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include "screenshot.h"
#include <QTimer>

class CaptureWorker : public QObject
{
    Q_OBJECT

    QTimer m_timer;
    QImage m_prevImage;

public:
    explicit CaptureWorker();
    ~CaptureWorker();

public slots:

    void Start();
    void onTimer();

signals:

    void Error(QString err);
    void NewScreenshotCaptured(const ScreenShot& shot);
};

#endif // CAPTUREWORKER_H
