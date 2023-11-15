#include "captureworker.h"

#include <QtWidgets>
#include <QCryptographicHash>

namespace
{
    QString imageHash(const QImage& image)
    {
        return "";
    }

    float imagesSimilarity(const QImage& image1, const QImage& image2)
    {
        return 0;
    }
}

CaptureWorker::CaptureWorker()
    : QObject(nullptr)
    , m_timer(this)
{
    connect(&m_timer, &QTimer::timeout, this, &CaptureWorker::onTimer);
}

CaptureWorker::~CaptureWorker()
{

}

void CaptureWorker::Start()
{
    m_timer.moveToThread(QThread::currentThread());
    m_timer.start(1000);
}

void CaptureWorker::onTimer()
{
    QScreen *screen = QGuiApplication::primaryScreen();

    Q_ASSERT(screen);

    ScreenShot shot;

    shot.image = screen->grabWindow(0).toImage();
    shot.hash = imageHash(shot.image);
    shot.similarity = imagesSimilarity(shot.image, m_prevImage);

    m_prevImage = shot.image;

    emit NewScreenshotCaptured(shot);
}
