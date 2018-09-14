#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QApplication>

#define FILE_DOWNLOAD_FILE_NAME_COLUMN           0
#define FILE_DOWNLOAD_SIZE_COLUMN                1
#define FILE_DOWNLOAD_STATUS_COLUMN              2
#define FILE_DOWNLOAD_PROGRESS_COLUMN            3

// 下载记录
struct FileDownloadRecord
{
    QString strFileName;         //文件名称
    qint64 nSize;                //大小
    int nStatus;                 //状态
    int nProgress;               //进度
};

class ProgressBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ProgressBarDelegate(QWidget *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROGRESSBARDELEGATE_H
