#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
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
signals:

public slots:

private:
    size_t block_size;
    size_t bput_size;
    qint64 file_size;
    QString path;
    QString file_name;
    uint progress;
    uint concurrency;
    uint block_number;
    uint size;
    QString token;
    QString url;

    QString bputUrl;
    QString blockUrl;
    QString fileUrl;
    uint block_id;

    ConfigSetting *setting;

    void getUploadInfo(QByteArray ba);
    upload_result uploadInfo;
    void bput_url(QString ctx, int offset);
    void block_url(uint size, uint bolck_num);
    void file_url();
    void make_block(uint offset);
    void mlk_url(uint offset);
};

#endif // UPLOAD_H
