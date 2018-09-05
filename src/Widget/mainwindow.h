#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/Widget/content.h"
#include "mitcontent.h"
#include "src/model/detailmodel.h"
#include "src/model/sortfilterproxymodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_myFiles_itemSelectionChanged();

    void on_myMit_itemSelectionChanged();

    void onClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Content *content;
	mitContent *MitContent;
    DetailModel *pModel;
    SortFilterProxyModel *pProxyModel;

    QList<FilesInfo> FilesList;
};

#endif // MAINWINDOW_H
