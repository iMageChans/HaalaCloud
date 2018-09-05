﻿#include "detail.h"
#include "ui_detail.h"

detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
    TableView = new QTableView(this);
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableView->horizontalHeader()->setStretchLastSection(true);
    TableView->horizontalHeader()->setHighlightSections(false);
    TableView->verticalHeader()->setVisible(false);
    TableView->setShowGrid(false);
    TableView->setFrameShape(QFrame::NoFrame);
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);
    TableView->setAlternatingRowColors(true);
    TableView->setStyleSheet("QTableView {border: none;border-top: 1px solid #E9E9E9;background:#FFFFFF;alternate-background-color:#F5F5F5;}"
                             "QTableView::item {border: none;font-size: 12px; color:#5A5A5A}"
                             "QTableView::item:selected {background:#2EC17C;font-size: 12px; color:#FFFFFF}"
                             "QTableView::indicator {width: 17px;height: 17px;}"
                             "QHeaderView::section {background:#F7F7F7;border: 0px solid #F7F7F7;min-height: 24px}");

    ui->TableLayout->addWidget(TableView);
}

detail::~detail()
{
	delete ui;
}
