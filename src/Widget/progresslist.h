#ifndef PROGRESSLIST_H
#define PROGRESSLIST_H

#include <QWidget>
#include <QTableView>

namespace Ui {
class ProgressList;
}

class ProgressList : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressList(QWidget *parent = nullptr);
    ~ProgressList();

    QTableView *TableView;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProgressList *ui;
};

#endif // PROGRESSLIST_H
