#include "sortfilterproxymodel.h"

SortFilterProxyModel::SortFilterProxyModel(QWidget *parent) : QSortFilterProxyModel (parent)
{

}

bool SortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if (!source_left.isValid() || !source_right.isValid())
        return false;

    if ((source_left.column() == 2) && (source_right.column() == 2))
    {
        QModelIndex sizeLeftIndex = sourceModel()->index(source_left.row(), 4);
        QModelIndex sizeRightIndex = sourceModel()->index(source_right.row(), 4);

        QVariant leftData = sourceModel()->data(sizeLeftIndex);
        QVariant rightData = sourceModel()->data(sizeRightIndex);

        if (leftData.canConvert<qint64>() && rightData.canConvert<qint64>())
        {
            return leftData.toLongLong() < rightData.toLongLong();
        }
    }

    return QSortFilterProxyModel::lessThan(source_left, source_right);
}
