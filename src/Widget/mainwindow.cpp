#include "src/Widget/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Widget/filesheaderview.h"
#include "src/Delegate/checkboxdelegate.h"

#include <QListWidgetItem>
#include <QPixmap>
#include <QPainter>

#include <QDebug>
#include <QSortFilterProxyModel>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap allFiles(QString(":/assets/assets/image.png"));
    QPixmap MyImage(QString(":/assets/assets/image.png"));
    QPixmap MyVideo(QString(":/assets/assets/image.png"));
    QPixmap upload(QString(":/assets/assets/image.png"));
    QPixmap download(QString(":/assets/assets/image.png"));
    QPixmap mitDone(QString(":/assets/assets/image.png"));
    QPixmap trash(QString(":/assets/assets/image.png"));

    QListWidgetItem *allFilesitem = new QListWidgetItem(QIcon(allFiles.scaled(QSize(15,15))),tr("全部文件"));
    QListWidgetItem *MyImageitem = new QListWidgetItem(QIcon(MyImage.scaled(QSize(15,15))),"图片");
    QListWidgetItem *MyVideoitem = new QListWidgetItem(QIcon(MyVideo.scaled(QSize(15,15))),"视频");

    QListWidgetItem *Uploaditem = new QListWidgetItem(QIcon(upload.scaled(QSize(15,15))),"正在上传");
    QListWidgetItem *Downloaditem = new QListWidgetItem(QIcon(download.scaled(QSize(15,15))),"正在下载");
    QListWidgetItem *mitDoneitem = new QListWidgetItem(QIcon(mitDone.scaled(QSize(15,15))),"传输完成");
    QListWidgetItem *trashitem = new QListWidgetItem(QIcon(trash.scaled(QSize(15,15))),"垃圾箱");

    ui->myFiles->addItem(allFilesitem);
    ui->myFiles->addItem(MyImageitem);
    ui->myFiles->addItem(MyVideoitem);

    ui->myMit->addItem(Uploaditem);
    ui->myMit->addItem(Downloaditem);
    ui->myMit->addItem(mitDoneitem);
    ui->myMit->addItem(trashitem);

    QWidget *spacingView = new QWidget;
    spacingView->setMaximumWidth(1);
    spacingView->setMinimumWidth(1);
    spacingView->setStyleSheet("background:#E9E9E9");
    ui->MainLayout->addWidget(spacingView,0,1);

	MitContent = new mitContent;
	QObject::connect(ui->myMit, SIGNAL(currentRowChanged(int)), MitContent->stack, SLOT(setCurrentIndex(int)));
	ui->MainLayout->addWidget(MitContent,0,2);

    content = new Content;														
    QObject::connect(ui->myFiles, SIGNAL(currentRowChanged(int)), content->stack, SLOT(setCurrentIndex(int)));
    ui->MainLayout->addWidget(content,0,2);
	ui->MainLayout->setSpacing(0);
	ui->MainLayout->setMargin(0);

    QPixmap pixmapa(":/assets/assets/2.png");
    QPixmap pixmap(75,75);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 75, 75);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 75, 75, pixmapa);
    ui->icon->setPixmap(pixmap);

    pModel = new DetailModel;
    pProxyModel = new SortFilterProxyModel(this);
    FilesHeaderView *pHeader = new FilesHeaderView(Qt::Horizontal, this);
    CheckBoxDelegate *pDelegate = new CheckBoxDelegate(this);

    pProxyModel->setSourceModel(pModel);
    content->Files->TableView->setModel(pProxyModel);
    content->Files->TableView->setSortingEnabled(true);
    content->Files->TableView->setHorizontalHeader(pHeader);
    content->Files->TableView->setItemDelegate(pDelegate);
    pHeader->setSectionResizeMode(QHeaderView::Stretch);
    pHeader->setSectionResizeMode(0, QHeaderView::Fixed);

    content->Files->TableView->setColumnWidth(0, 30);
    content->Files->TableView->setColumnHidden(4, true);
    content->Files->TableView->sortByColumn(3, Qt::AscendingOrder);

    connect(pModel, SIGNAL(stateChanged(int)), pHeader, SLOT(onStateChanged(int)));
    connect(pHeader, SIGNAL(stateChanged(int)), pModel, SLOT(onStateChanged(int)));
    connect(content->Files->TableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClicked(QModelIndex)));

    for (int i = 0; i < 5; ++i)
    {
        int nIndex = qrand()%20 + 1;
        int nHour = qrand()%24;
        int nMinute = qrand()%60;
        int nSecond = qrand()%60;
        int nBytes = qrand()%100000;

        QDateTime dateTime(QDate(2018, 9, 3), QTime(nHour, nMinute, nSecond));

        FilesInfo record;
        record.FileName = QString("Name %1.cpp").arg(nIndex);
        record.Size = nBytes;
        record.ReviseTime = dateTime;
        record.bChecked = false;
        FilesList.append(record);
    }
    pModel->updateData(FilesList);
}

void MainWindow::onClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        QModelIndex sourceIndex = pProxyModel->mapToSource(index);
        QModelIndex checkIndex = pModel->index(sourceIndex.row(), 0);
        bool bChecked = pModel->data(checkIndex, Qt::UserRole).toBool();
        pModel->setData(checkIndex, !bChecked, Qt::UserRole);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_myFiles_itemSelectionChanged()
{
    MitContent->hide();
    content->show();

	for (int i = 0; i < 3; i++)
	{
		QListWidgetItem *item = ui->myMit->item(i);
		item->setSelected(false);
	}
}

void MainWindow::on_myMit_itemSelectionChanged()
{
    content->hide();
    MitContent->show();

	for (int i = 0; i < 3; i++)
	{
		QListWidgetItem *item = ui->myFiles->item(i);
		item->setSelected(false);
	}
}
