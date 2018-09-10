#ifndef DETAILMODEL_H
#define DETAILMODEL_H

#include <QAbstractItemModel>
#include <QDateTime>

#include "src/util/tool.h"

typedef struct{
    QString FileName;
    qint64  Size;
    QDateTime ReviseTime;
    bool bChecked;
}FilesInfo;

class DetailModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DetailModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void updateData(QList<FilesInfo> recordList);

private:
    QList<FilesInfo> m_recordList;
    Tool *tool;

public slots:
    void onStateChanged();
    void onStateChanged(int state);

signals:
    void stateChanged(int state);
};

#endif // DETAILMODEL_H
