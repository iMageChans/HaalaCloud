#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QTableView>

namespace Ui {
class detail;
}

class detail : public QWidget
{
    Q_OBJECT

public:
    explicit detail(QWidget *parent = nullptr);
    ~detail();

    QTableView *TableView;

private:
    Ui::detail *ui;
};

#endif // DETAIL_H
