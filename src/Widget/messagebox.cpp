#include "messagebox.h"
#include "ui_messagebox.h"

MessageBox::MessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::setBoxText(QString content)
{
    ui->label->setText(content);
}

void MessageBox::on_pushButton_clicked()
{
    this->close();
}

void MessageBox::on_pushButton_3_clicked()
{
    this->close();
}
