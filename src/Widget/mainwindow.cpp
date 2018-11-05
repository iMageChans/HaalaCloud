#include "src/Widget/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Widget/filesheaderview.h"
#include "src/Delegate/checkboxdelegate.h"
#include "src/Delegate/tableviewdelegate.h"
#include "src/Delegate/progressbardelegate.h"
#include "src/util/filedownloadthread.h"
#include "src/util/tool.h"
#include "src/util/request.h"
#include "src/Widget/login.h"
#include "src/model/upload.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QPixmap>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>

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
    setNetwork();
    setWidgetList();
    setAllFilesList();
    setUploadList();


    FileDownloadThread *FDT = new FileDownloadThread;
    connect(FDT, SIGNAL(transfer(QList<FilesStatusInfo>)), this, SLOT(updateUploadList(QList<FilesStatusInfo>)));
    connect(FDT, SIGNAL(finished()), FDT, SLOT(deleteLater()));
    FDT->start();
    setting = new ConfigSetting;
}

void MainWindow::setNetwork()
{
    QByteArray ba;
    QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/files/page", setting->getSystemConfig("token"), QByteArray(), ba);
    if(ret==QNetworkReply::NoError){
        FilesModel *model = new FilesModel;
        model->setFilesModel(ba);
        Files files = model->getFilesModel();
        FilesList = files.result.list;
    }else{
        qDebug() << QStringLiteral("%1 error:%2").arg("/v1/files/page").arg(ret);
    }
}

void MainWindow::setUploadList()
{
    uploadModel = new ProgressModel;
    FilesHeaderView *pHeader = new FilesHeaderView(Qt::Horizontal, this);

    sendView->Upload->TableView->setHorizontalHeader(pHeader);
    sendView->Upload->TableView->setModel(uploadModel);
    sendView->Upload->TableView->setSortingEnabled(true);

    pHeader->setSectionResizeMode(QHeaderView::Stretch);

#if defined(Q_OS_MAC)
    CheckBoxDelegate *pDelegate = new CheckBoxDelegate(this);
    sendView->Upload->TableView->setItemDelegate(pDelegate);

    TableViewDelegate *tableViewDelegate = new TableViewDelegate(this);
    sendView->Upload->TableView->setItemDelegate(tableViewDelegate);
    tableViewDelegate->setColumn(4);

    ProgressBarDelegate *progressDelegate = new ProgressBarDelegate(this);
    sendView->Upload->TableView->setItemDelegate(progressDelegate);

    pHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(2, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(4, QHeaderView::Fixed);

    sendView->Upload->TableView->setColumnWidth(0, 30);
    sendView->Upload->TableView->setColumnWidth(2, 150);
    sendView->Upload->TableView->setColumnWidth(3, 200);
    sendView->Upload->TableView->setColumnWidth(4, 150);
#elif defined(Q_OS_WIN32)
    CheckBoxDelegate *pDelegate = new CheckBoxDelegate(this);
    sendView->Upload->TableView->setItemDelegate(pDelegate);

    TableViewDelegate *tableViewDelegate = new TableViewDelegate(this);
    sendView->Upload->TableView->setItemDelegate(tableViewDelegate);
    tableViewDelegate->setColumn(4);

    ProgressBarDelegate *progressDelegate = new ProgressBarDelegate(this);
    sendView->Upload->TableView->setItemDelegate(progressDelegate);

    pHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(2, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(4, QHeaderView::Fixed);

    sendView->Upload->TableView->setColumnWidth(0, 30);
    sendView->Upload->TableView->setColumnWidth(2, 150);
    sendView->Upload->TableView->setColumnWidth(3, 200);
    sendView->Upload->TableView->setColumnWidth(4, 150);
#endif
    connect(uploadModel, SIGNAL(stateChanged(int)), pHeader, SLOT(onStateChanged(int)));
    connect(pHeader, SIGNAL(stateChanged(int)), uploadModel, SLOT(onStateChanged(int)));
    connect(sendView->Upload->TableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClicked(QModelIndex)));
}

void MainWindow::updateUploadList(QList<FilesStatusInfo> filesStatusInfo){
    uploadModel->updateData(filesStatusInfo);
}

void MainWindow::setAllFilesList()
{
    detaiModel = new DetailModel;
    pProxyModel = new SortFilterProxyModel(this);
    FilesHeaderView *pHeader = new FilesHeaderView(Qt::Horizontal, this);

    pProxyModel->setSourceModel(detaiModel);
    content->Files->TableView->setModel(pProxyModel);
    content->Files->TableView->setSortingEnabled(true);
    content->Files->TableView->setHorizontalHeader(pHeader);

    pHeader->setSectionResizeMode(QHeaderView::Stretch);

#if defined(Q_OS_MAC)
    CheckBoxDelegate *pDelegate = new CheckBoxDelegate(this);
    content->Files->TableView->setItemDelegate(pDelegate);

    TableViewDelegate *tableViewDelegate = new TableViewDelegate(this);
    content->Files->TableView->setItemDelegate(tableViewDelegate);
    tableViewDelegate->setColumn(2);

    pHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(2, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(4, QHeaderView::Fixed);

    content->Files->TableView->setColumnWidth(0, 30);
    content->Files->TableView->setColumnWidth(2, 80);
    content->Files->TableView->setColumnWidth(3, 100);
    content->Files->TableView->setColumnWidth(4, 150);
    content->Files->TableView->setColumnHidden(5, true);
#elif defined(Q_OS_WIN32)
    CheckBoxDelegate *pDelegate = new CheckBoxDelegate(this);
    content->Files->TableView->setItemDelegate(pDelegate);

    TableViewDelegate *tableViewDelegate = new TableViewDelegate(this);
    content->Files->TableView->setItemDelegate(tableViewDelegate);
    tableViewDelegate->setColumn(2);

    pHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(2, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    pHeader->setSectionResizeMode(4, QHeaderView::Fixed);

    content->Files->TableView->setColumnWidth(0, 30);
    content->Files->TableView->setColumnWidth(2, 80);
    content->Files->TableView->setColumnWidth(3, 150);
    content->Files->TableView->setColumnWidth(4, 110);
    content->Files->TableView->setColumnHidden(5, true);
#endif
    connect(detaiModel, SIGNAL(stateChanged(int)), pHeader, SLOT(onStateChanged(int)));
    connect(pHeader, SIGNAL(stateChanged(int)), detaiModel, SLOT(onStateChanged(int)));
    connect(content->Files->TableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClicked(QModelIndex)));
    detaiModel->updateData(FilesList);
}

void MainWindow::setWidgetList()
{
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

    sendView = new mitContent;
    QObject::connect(ui->myMit, SIGNAL(currentRowChanged(int)), sendView->stack, SLOT(setCurrentIndex(int)));
    ui->MainLayout->addWidget(sendView,0,2);

    content = new Content;
    QObject::connect(ui->myFiles, SIGNAL(currentRowChanged(int)), content->stack, SLOT(setCurrentIndex(int)));
    ui->MainLayout->addWidget(content,0,2);
    ui->MainLayout->setSpacing(0);
    ui->MainLayout->setMargin(0);
}

void MainWindow::setUserInfo(User user)
{
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

    ui->name->setText(user.result.name);

    ui->progressBar->setRange(0, int(user.result.spaceCapacity));
    ui->progressBar->setValue(int(user.result.spaceUsed));

    Tool *tool = new Tool;
    qDebug() << user.result.spaceUsed;
    qDebug() << user.result.spaceCapacity;
    ui->capacity->setText(QString("%1/%2").arg(user.result.spaceUsed / 1024).arg(tool->bytesToGBMBKB(user.result.spaceCapacity)));
}

void MainWindow::onClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        QModelIndex sourceIndex = pProxyModel->mapToSource(index);
        QModelIndex checkIndex = detaiModel->index(sourceIndex.row(), 0);
        bool bChecked = detaiModel->data(checkIndex, Qt::UserRole).toBool();
        detaiModel->setData(checkIndex, !bChecked, Qt::UserRole);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_myFiles_itemSelectionChanged()
{
    sendView->hide();
    content->show();

    for (int i = 0; i < 4; i++)
	{
		QListWidgetItem *item = ui->myMit->item(i);
		item->setSelected(false);
	}
}

void MainWindow::on_myMit_itemSelectionChanged()
{
    content->hide();
    sendView->show();

	for (int i = 0; i < 3; i++)
	{
		QListWidgetItem *item = ui->myFiles->item(i);
		item->setSelected(false);
	}
}

void MainWindow::on_loginOut_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    qint64 ptime = time.toTime_t();
    QByteArray ba;
    QByteArray postBa;
    QJsonObject Json;
    Json.insert("time", ptime);
    QJsonDocument docum;
    docum.setObject(Json);
    postBa = docum.toJson(QJsonDocument::Compact);

    QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/user/logout", setting->getSystemConfig("token"), postBa, ba);
    if(ret==QNetworkReply::NoError){
        setting->setSystemConfig("Remember", QString::number(0));
        setting->setSystemConfig("AotuLogin", QString::number(0));
        setting->deleteSystemConfig("token");
        Login *login = new Login;
        login->show();
        this->close();
    }else{
        qDebug() << QStringLiteral("%1 error:%2").arg("/v1/user/logout").arg(ret);
    }
}
