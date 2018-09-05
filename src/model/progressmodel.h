#ifndef PROGRESSMODEL_H
#define PROGRESSMODEL_H

#include <QJsonObject>

#include <QAbstractItemModel>

class ProgressModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProgressModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateData(QList<QJsonObject> recordList);

private:
    QList<QJsonObject> m_recordList;
};

#endif // PROGRESSMODEL_H
