#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QObject>
#include <QByteArray>
#include <QDateTime>

typedef struct{
    QString uuid;
    QString storeId;
    int userId;
    QString path;
    QString name;
    QString ext;
    qint64 size;
    QString parent;
    int type;
    QDateTime atime;
    QDateTime ctime;
    QDateTime mtime;
    int version;
    bool locking;
}ListInfo;

typedef struct{
    QString uuid;
    QString storeId;
    int userId;
    QString path;
    QString name;
    QString ext;
    qint64 size;
    QString parent;
    int type;
    QDateTime atime;
    QDateTime ctime;
    int mtime;
    int version;
    bool locking;
    QString mime;
    int preview;
    int flag;
    bool bChecked;
}FileInfo;

typedef struct{
    int page;
    int pageSize;
    int totalCount;
    int totalPage;
    QList<FileInfo> list;
    ListInfo info;
}Result;

typedef struct{
    int status;
    Result result;
    QString code;
    bool success;
    QString token;
}Files;

class FilesModel : public QObject
{
    Q_OBJECT
public:
    explicit FilesModel(QObject *parent = nullptr);
    void setFilesModel(QByteArray &ba);
    Files getFilesModel() const;
signals:

public slots:

private:
    Files files;
    FileInfo fileInfo;
    QList<FileInfo> lists;
};

#endif // FILESMODEL_H
