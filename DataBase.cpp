#include "DataBase.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>

constexpr char c_szDatabasePath[] = "screen-shots.db";

DataBase::DataBase()
{

}

void DataBase::Connect()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(c_szDatabasePath);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
        return;
    }

    auto tables = m_db.tables();

    // add tables
    if(tables.empty())
    {
        QSqlQuery query;
        query.prepare(
            "CREATE TABLE screenshots ( "
                "record_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
                "hash VARCHAR(128), "
                "similarity FLOAT(3.2), "
                "bitmap LONGBLOB"
            ");");

        if(!query.exec())
        {
            qDebug() << "Error: failed to create table: " << query.lastError().text();
            return;
        }
    }
}

void DataBase::AddScreenShot(const ScreenShot& shot)
{
    QSqlQuery query;
    query.prepare("INSERT INTO screenshots (hash, similarity, bitmap) VALUES ("
        ":hash, :similarity, :bitmap"
        ");");

    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    shot.image.save(&buffer, "PNG");

    query.bindValue(":hash", shot.hash);
    query.bindValue(":similarity", shot.similarity);
    query.bindValue(":bitmap", ba, QSql::In | QSql::Binary);

    if(!query.exec())
    {
        qDebug() << "Error: failed to inset screenshot: " << query.lastError().text();
        return;
    }

    qDebug() << "Success: screenshot inserted OK; size: " << ba.size();
}
