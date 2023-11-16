#ifndef SQLIMAGETABLEMODEL_H
#define SQLIMAGETABLEMODEL_H

#include <QSqlTableModel>
#include <QIcon>

class SqlImageTableModel : public QSqlTableModel
{
    Q_OBJECT

    mutable std::unordered_map<std::string, QPixmap> m_imagesCache;

    const QPixmap& getCachedImage(const QString& hash, QByteArray& origin) const;

public:

    SqlImageTableModel();

public:
    int columnCount(const QModelIndex& idx) const override;
    QVariant data(const QModelIndex& idx, int role) const override;
};


#endif // SQLIMAGETABLEMODEL_H
