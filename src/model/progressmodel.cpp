﻿#include "progressmodel.h"

#include <QColor>
#include <QDebug>

ProgressModel::ProgressModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    tool = new Tool;
}

void ProgressModel::updateData(QList<FilesStatusInfo> recordList)
{
    m_recordList = recordList;
    beginResetModel();
    endResetModel();
}

QVariant ProgressModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QStringLiteral("状态");

            if (section == 4)
                return QStringLiteral("操作");
        }
    }
    }

    return QVariant();
}

QModelIndex ProgressModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    return createIndex(row, column);
}

QModelIndex ProgressModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ProgressModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_recordList.count();
    return m_recordList.count();
}

int ProgressModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 5;
    return 5;
}

bool ProgressModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    FilesStatusInfo record = m_recordList.at(index.row());
    switch (role)
    {
        case Qt::DisplayRole:
        {
            if (nColumn == 1)
            {
                record.FileName = value.toString();
            }
            else if (nColumn == 2)
            {
                record.Size = value.toLongLong();
            }
            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);

            return true;
        }
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
            if (nColumn == 3)
            {
                record.nProgress = value.toInt();
                qDebug() << record.nProgress;
                m_recordList.replace(index.row(), record);
            }
        }
    return false;
    }
}

QVariant ProgressModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
             return QVariant();

         int nRow = index.row();
         int nColumn = index.column();
         FilesStatusInfo record = m_recordList.at(nRow);

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
             return "";
         }
#if defined(Q_OS_MAC)
         case Qt::CheckStateRole:
#endif
         case Qt::UserRole:
         {
             if (nColumn == 0)
                 return record.bChecked;

             if (nColumn == 3)
                 return record.nProgress;
         }
         }
         return QVariant();
 }


Qt::ItemFlags ProgressModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return flags;
}

void ProgressModel::onStateChanged()
{
    Qt::CheckState state = Qt::Unchecked;
    int nCount = m_recordList.count();
    int nSelectedCount = 0;
    FilesStatusInfo record;
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

void ProgressModel::onStateChanged(int state)
{
    QModelIndex index;
    for (int i = 0; i < rowCount(); ++i)
    {
        index = this->index(i, 0);
        setData(index, state == Qt::Checked, Qt::CheckStateRole);
    }
}
