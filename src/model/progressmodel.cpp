#include "progressmodel.h"

ProgressModel::ProgressModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

void ProgressModel::updateData(QList<QJsonObject> recordList)
{
    m_recordList = recordList;
    beginResetModel();
    endResetModel();
}

QVariant ProgressModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role){
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
        {
            if (orientation == Qt::Horizontal)
            {
                if (section == 1)
                    return QStringLiteral("文件名");

                if (section == 1)
                    return QStringLiteral("大小");

                if (section == 1)
                    return QStringLiteral("状态");

                if (section == 1)
                    return QStringLiteral("操作");
            }
        }
        default:
            return QVariant();
    }
    return QVariant();
}

QModelIndex ProgressModel::index(int row, int column, const QModelIndex &parent) const
{
	return createIndex(row, column);
}

QModelIndex ProgressModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
}

int ProgressModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ProgressModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ProgressModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
