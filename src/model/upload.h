#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include "src/util/configsetting.h"

typedef struct{
    QString ctx;
    QString checksum;
    QString uuid;
    int crc32;
    int offset;
    int BlockNumber;
}BlockInfo;

typedef struct{
    QString name;
    QString parent;
    QString path;
    QString token;
    int type;
    QString uploadUrl;
    int version;
}uploadInfo;

typedef struct{
    int status;
    uploadInfo result;
    QString code;
    bool success;
    QString token;
}upload_result;

class Upload : public QObject
{
    Q_OBJECT
public:
    explicit Upload(QObject *parent = nullptr);
    void setUploadConfig(QString filesPath);
    void Run();
signals:

public slots:

private:
    uint block_size;
    uint concurrency;

    qint64 file_size;
    QString file_name;
    QString file_path;
    QString path;

    upload_result uploadInfo;

    QNetworkAccessManager *manager;

    ConfigSetting *setting;

    void getUploadInfo(QByteArray ba);
    BlockInfo getMultipartUploadResult(QByteArray data, int i, QString uuid);
};

#endif // UPLOAD_H
