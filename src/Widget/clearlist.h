#ifndef CLEARLIST_H
#define CLEARLIST_H

#include <QWidget>

namespace Ui {
class ClearList;
}

class ClearList : public QWidget
{
    Q_OBJECT

public:
    explicit ClearList(QWidget *parent = nullptr);
    ~ClearList();

private:
    Ui::ClearList *ui;
};

#endif // CLEARLIST_H
