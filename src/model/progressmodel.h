#ifndef PROGRESSMODEL_H
#define PROGRESSMODEL_H

#include <QJsonObject>
#include <QAbstractItemModel>

#include "src/util/tool.h"

typedef struct{
    QString FileName;
    qint64  Size;
    int nStatus;
    int nProgress;
    bool bChecked;
}FilesStatusInfo;

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

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void updateData(QList<FilesStatusInfo> recordList);

private:
    QList<FilesStatusInfo> m_recordList;
    Tool *tool;

public slots:
    void onStateChanged();
    void onStateChanged(int state);

signals:
    void stateChanged(int state);
};

#endif // PROGRESSMODEL_H
