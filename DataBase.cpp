#include "DataBase.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>
#include <QSqlRecord>

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
            emit Error("Failed to create table: " + query.lastError().text());
        }
    }
}

void DataBase::AddScreenShot(const ScreenShot& shot)
{
    QSqlQuery query;
    query.prepare("INSERT INTO screenshots (hash, similarity, bitmap) VALUES ("
        ":hash, :similarity, :bitmap"
        ");");

    query.bindValue(":hash", shot.hash);
    query.bindValue(":similarity", shot.similarity);
    query.bindValue(":bitmap", shot.pngImage, QSql::In | QSql::Binary);
    query.finish();

    if(!query.exec())
    {
        emit Error("Failed to add new screenshot.");
    }
}

QByteArray DataBase::GetLastCapturedImage()
{
    QSqlQuery query;

    query.prepare("SELECT bitmap, MAX(record_id) FROM screenshots GROUP BY record_id LIMIT  1;");
    //query.prepare("SELECT * FROM screenshots");
    query.finish();

    if(!query.exec())
    {
        emit Error("Failed to exec select statement.");
        return {};
    }

    while (query.next()) {

        int fieldNo = query.record().indexOf("bitmap");
        auto image = query.value(fieldNo);
        return image.toByteArray();
    }

    return {};
}
