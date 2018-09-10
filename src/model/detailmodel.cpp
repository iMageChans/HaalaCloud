﻿#include "detailmodel.h"
#include <QColor>

DetailModel::DetailModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    tool = new Tool;
}

void DetailModel::updateData(QList<FilesInfo> recordList)
{
    m_recordList = recordList;
    beginResetModel();
    endResetModel();
}

QVariant DetailModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 1)
                return QStringLiteral("文件名");

            if (section == 2)
                return QStringLiteral("大小");

            if (section == 3)
                return QStringLiteral("修改日期");

            if (section == 4)
                return QStringLiteral("大小（字节）");
        }
    }
    }

    return QVariant();
}

QModelIndex DetailModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    return createIndex(row, column);
}

QModelIndex DetailModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int DetailModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_recordList.count();
    return m_recordList.count();
}

int DetailModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 5;
    return 5;
}

bool DetailModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    FilesInfo record = m_recordList.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
    {
        if (nColumn == 1)
        {
            record.FileName = value.toString();
        }
        else if (nColumn == 2 || nColumn == 4)
        {
            record.Size = value.toLongLong();
        }
        else if (nColumn == 3)
        {
            record.ReviseTime = value.toDateTime();
        }
        m_recordList.replace(index.row(), record);
        emit dataChanged(index, index);

        if ((nColumn == 2) || (nColumn == 4))
        {
            int nSizeColumn = (nColumn == 2) ? 4 : 2;
            QModelIndex sizeIndex = this->index(index.row(), nSizeColumn);
            emit dataChanged(sizeIndex, sizeIndex);
        }

        return true;
    }
#if defined(Q_OS_MAC)
    case Qt::CheckStateRole:
    {
        if (nColumn == 0)
        {
            record.bChecked = (value.toInt() == Qt::Checked);

            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);
            return true;
        }
    }
#elif defined(Q_OS_WIN32)
    case Qt::CheckStateRole:
    case Qt::UserRole:
    {
        if (nColumn == 0)
        {
            record.bChecked = value.toBool();

            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);

            if (role == Qt::UserRole)
                onStateChanged();
            return true;
        }
    }
#endif
    }
    return false;
}

QVariant DetailModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        int nRow = index.row();
        int nColumn = index.column();
        FilesInfo record = m_recordList.at(nRow);

        switch (role)
        {
        case Qt::TextColorRole:
            return QColor(Qt::white);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
        {
            if (nColumn == 1)
            {
                return record.FileName;
            }
            else if (nColumn == 2)
            {
                return tool->bytesToGBMBKB(record.Size);
            }
            else if (nColumn == 3)
            {
                return record.ReviseTime;
            }
            else if (nColumn == 4)
            {
                return record.Size;
            }
            return "";
        }
#if defined(Q_OS_MAC)
        case Qt::CheckStateRole:
        {
            if (nColumn == 0)
                return record.bChecked ? Qt::Checked : Qt::Unchecked;
        }
#elif defined(Q_OS_WIN32)
        case Qt::UserRole:
        {
            if (nColumn == 0)
                return record.bChecked;
        }
#endif
        }
        return QVariant();
}

Qt::ItemFlags DetailModel::flags(const QModelIndex &index) const
{
#if defined(Q_OS_MAC)
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
#elif defined(Q_OS_WIN32)
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
#endif
}

void DetailModel::onStateChanged()
{
    Qt::CheckState state = Qt::Unchecked;
    int nCount = m_recordList.count();
    int nSelectedCount = 0;
    FilesInfo record;
    for (int i = 0; i < nCount; ++i)
    {
        record = m_recordList.at(i);
        if (record.bChecked)
            ++nSelectedCount;
    }

    if (nSelectedCount >= nCount)
    {
        state = Qt::Checked;
    }
    else if (nSelectedCount > 0)
    {
        state = Qt::PartiallyChecked;
    }

    emit stateChanged(state);
}

void DetailModel::onStateChanged(int state)
{
    QModelIndex index;
    for (int i = 0; i < rowCount(); ++i)
    {
        index = this->index(i, 0);
        setData(index, state == Qt::Checked, Qt::CheckStateRole);
    }
}
