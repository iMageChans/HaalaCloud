#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/Widget/content.h"
#include "mitcontent.h"
#include "src/model/detailmodel.h"
#include "src/model/sortfilterproxymodel.h"
#include "src/model/usermodel.h"
#include "src/util/configsetting.h"

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

private:
    Ui::MainWindow *ui;
    Content *content;
	mitContent *MitContent;
    DetailModel *pModel;
    SortFilterProxyModel *pProxyModel;
    ConfigSetting *setting;

    QList<FilesInfo> FilesList;
};

#endif // MAINWINDOW_H
