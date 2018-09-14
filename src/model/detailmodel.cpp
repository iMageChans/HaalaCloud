#include "src/model/detailmodel.h"
#include <QColor>
#include <QVariant>

DetailModel::DetailModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    tool = new Tool;
}

void DetailModel::updateData(QList<FileInfo> recordList)
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
                return QStringLiteral("");

            if (section == 3)
                return QStringLiteral("大小");

            if (section == 4)
                return QStringLiteral("修改日期");

            if (section == 5)
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
        return 6;
    return 6;
}

bool DetailModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    FileInfo record = m_recordList.at(index.row());
    switch (role)
    {
        case Qt::DisplayRole:
        {
            if (nColumn == 1)
            {
                record.name = value.toString();
            }
            else if (nColumn == 3 || nColumn == 5)
            {
                record.size = value.toLongLong();
            }
            else if (nColumn == 4)
            {
                record.atime = value.toDateTime();
            }
            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);

            if ((nColumn == 3) || (nColumn == 5))
            {
                int nSizeColumn = (nColumn == 3) ? 5 : 3;
                QModelIndex sizeIndex = this->index(index.row(), nSizeColumn);
                emit dataChanged(sizeIndex, sizeIndex);
            }

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
        }
    return false;
    }
}

QVariant DetailModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
             return QVariant();

         int nRow = index.row();
         int nColumn = index.column();
         FileInfo record = m_recordList.at(nRow);

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
                 return record.name;
             }
             else if (nColumn == 3)
             {
                 return tool->bytesToGBMBKB(record.size);
             }
             else if (nColumn == 4)
             {
                 return record.atime;
             }
             else if (nColumn == 5)
             {
                 return record.size;
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
         }
         }
         return QVariant();
 }


Qt::ItemFlags DetailModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return flags;
}

void DetailModel::onStateChanged()
{
    Qt::CheckState state = Qt::Unchecked;
    int nCount = m_recordList.count();
    int nSelectedCount = 0;
    FileInfo record;
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
