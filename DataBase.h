#ifndef DATABASE_H
#define DATABASE_H

#include "screenshot.h"

#include <QSqlDatabase>

class DataBase : public QObject
{
    Q_OBJECT

    QSqlDatabase m_db;

public:

    DataBase();

    // can throw
    void Connect();
    void AddScreenShot(const ScreenShot& shot);
    QByteArray GetLastCapturedImage();

signals:

    void Error(QString err);

};


#endif // DATABASE_H
