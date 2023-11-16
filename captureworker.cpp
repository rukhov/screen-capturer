#include "captureworker.h"

#include <QtWidgets>
#include <QCryptographicHash>

namespace
{
    QString calcHash(const QByteArray& array)
    {
        QCryptographicHash hf(QCryptographicHash::Md4);
        hf.addData(array);
        QString hash = hf.result().toBase64();
        return hash;
    }

    float imagesSimilarity(const QImage& image1, const QImage& image2)
    {
        int cx = std::min(image1.width(), image2.width());
        int cy = std::min(image1.height(), image2.height());

        int equalPixelsCount = 0;

        for( int x = 0; x < cx; ++x)
        {
            for(int y = 0; y < cy; ++y)
            {
                if(image1.pixel(x, y)==image2.pixel(x, y))
                    ++equalPixelsCount;
            }
        }

        if(cx*cy == 0)
            return 0.;

        return 100. * equalPixelsCount / (cx * cy);
    }
}

CaptureWorker::CaptureWorker(QByteArray&& prevPngImage)
    : QObject(nullptr)
    , m_timer(this)
{
    QBuffer buffer(&prevPngImage);
    buffer.open(QIODevice::ReadOnly);
    m_prevImage.load(&buffer, "PNG");

    connect(&m_timer, &QTimer::timeout, this, &CaptureWorker::onTimer);
}

CaptureWorker::~CaptureWorker()
{

}

void CaptureWorker::Start()
{
    m_timer.moveToThread(QThread::currentThread());
    // one minute timer
    m_timer.start(60*1000);
    // make first shot immediately
    onTimer();
}

void CaptureWorker::onTimer()
{
    QScreen *screen = QGuiApplication::primaryScreen();

    Q_ASSERT(screen);

    ScreenShot shot;

    auto image = screen->grabWindow(0).toImage();

    QBuffer buffer(&shot.pngImage);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    shot.hash = calcHash(shot.pngImage);
    shot.similarity = imagesSimilarity(image, m_prevImage);

    m_prevImage = image;

    emit NewScreenshotCaptured(shot);
}
