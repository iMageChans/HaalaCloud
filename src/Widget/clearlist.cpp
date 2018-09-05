#include "clearlist.h"
#include "ui_clearlist.h"

ClearList::ClearList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClearList)
{
    ui->setupUi(this);
}

ClearList::~ClearList()
{
    delete ui;
}
