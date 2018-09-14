#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/Widget/content.h"
#include "src/Widget/mitcontent.h"
#include "src/model/detailmodel.h"
#include "src/model/progressmodel.h"
#include "src/model/sortfilterproxymodel.h"
#include "src/model/usermodel.h"
#include "src/util/configsetting.h"
#include "src/model/filesmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUserInfo(User user);

private slots:
    void on_myFiles_itemSelectionChanged();

    void on_myMit_itemSelectionChanged();

    void onClicked(const QModelIndex &index);

    void on_loginOut_clicked();

    void updateUploadList(QList<FilesStatusInfo> filesStatusInfo);

private:
    void setWidgetList();
    void setAllFilesList();
    void setUploadList();
    void setNetwork();

    Ui::MainWindow *ui;
    Content *content;
    mitContent *sendView;
    DetailModel *detaiModel;
    ProgressModel *uploadModel;
    SortFilterProxyModel *pProxyModel;
    ConfigSetting *setting;

    QList<FileInfo> FilesList;
    QList<FilesStatusInfo> uploadInfoList;
};

#endif // MAINWINDOW_H
