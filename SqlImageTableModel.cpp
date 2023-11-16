#include "SqlImageTableModel.h"

#include <QBuffer>

const QPixmap& SqlImageTableModel::getCachedImage(const QString& hash, QByteArray& origin) const
{
    auto hashStr = hash.toStdString();

    auto it = m_imagesCache.find(hashStr);

    if(it != m_imagesCache.end())
        return it->second;

    QBuffer buffer(&origin);
    buffer.open(QIODevice::ReadOnly);
    QImage image;
    image.load(&buffer, "PNG");

    return m_imagesCache[hashStr] = QPixmap::fromImage(image.scaled(240,240));
}

SqlImageTableModel::SqlImageTableModel()
{
}

int SqlImageTableModel::columnCount(const QModelIndex& idx) const
{
    return QSqlTableModel::columnCount(idx);
}

QVariant SqlImageTableModel::data(const QModelIndex& idx, int role) const
{
    if(role == Qt::DisplayRole) {
        auto item = QSqlTableModel::data(idx.siblingAtColumn(2), role);
        return QString::number(item.toDouble());
    }

    if(role == Qt::DecorationRole) {
        auto itemHash = QSqlTableModel::data(idx.siblingAtColumn(1), Qt::DisplayRole);
        auto image = QSqlTableModel::data(idx.siblingAtColumn(3), Qt::DisplayRole);
        auto array = image.toByteArray();
        return QVariant(getCachedImage(itemHash.toString(), array));
    }

    return QSqlTableModel::data(idx, role);
}
