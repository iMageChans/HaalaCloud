#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

namespace Ui {
class MessageBox;
}

class MessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();

    void setBoxText(QString content);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MessageBox *ui;
};

#endif // MESSAGEBOX_H
