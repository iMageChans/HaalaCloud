#include "progresslist.h"
#include "ui_progresslist.h"

ProgressList::ProgressList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressList)
{
    ui->setupUi(this);
}

ProgressList::~ProgressList()
{
    delete ui;
}
