#include "captureworker.h"

#include <QtWidgets>

CaptureWorker::CaptureWorker(QObject *parent)
    : QObject(parent)
{
    m_timer.moveToThread(thread());
    connect(&m_timer, &QTimer::timeout, this, &CaptureWorker::onTimer);
}

CaptureWorker::~CaptureWorker()
{

}

void CaptureWorker::Start()
{
    m_timer.start(1000);
}

void CaptureWorker::onTimer()
{
    QScreen *screen = QGuiApplication::primaryScreen();

    Q_ASSERT(screen);

    auto pixmap = screen->grabWindow(0);

    //pixmap.
}
