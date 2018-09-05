#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QWidget>

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit SortFilterProxyModel(QWidget *parent = nullptr);

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private:
};

#endif // SORTFILTERPROXYMODEL_H
