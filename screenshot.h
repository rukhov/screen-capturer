#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QImage>

struct ScreenShot
{
    QString hash;
    QByteArray pngImage;
    float similarity;
};

Q_DECLARE_METATYPE(ScreenShot)

#endif // SCREENSHOT_H
