#ifndef PROGRESSLIST_H
#define PROGRESSLIST_H

#include <QWidget>

namespace Ui {
class ProgressList;
}

class ProgressList : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressList(QWidget *parent = nullptr);
    ~ProgressList();

private:
    Ui::ProgressList *ui;
};

#endif // PROGRESSLIST_H
