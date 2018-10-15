#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include "src/util/configsetting.h"

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
    void make_block(int offset);
signals:

public slots:

private:
    int block_size;
    int bput_size;
    qint64 file_size;
    QString path;
    QString file_name;
    QString file_path;
    uint progress;
    uint concurrency;
    int block_number;
    int size;
    QString token;
    QString url;

    QString bputUrl;
    QString blockUrl;
    QString fileUrl;
    int block_id;

    upload_result uploadInfo;

    QNetworkAccessManager *manager;

    ConfigSetting *setting;

    void getUploadInfo(QByteArray ba);
    void bput_url(QString ctx, int offset);
    void block_url(int size, int bolck_num);
    void file_url();
    void mlk_url(int offset);
};

#endif // UPLOAD_H
