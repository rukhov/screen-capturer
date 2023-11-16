#ifndef DATABASE_H
#define DATABASE_H

#include "screenshot.h"

#include <QSqlDatabase>

class DataBase
{
    QSqlDatabase m_db;

public:

    DataBase();

    // can throw
    void Connect();
    void AddScreenShot(const ScreenShot& shot);
    QByteArray GetLastCapturedImage();
};


#endif // DATABASE_H
