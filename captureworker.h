#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include <QObject>

class CaptureWorker : public QObject
{
    Q_OBJECT
public:
    explicit CaptureWorker(QObject *parent = nullptr);

signals:

};

#endif // CAPTUREWORKER_H
