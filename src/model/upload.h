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
    int progress;
    int concurrency;
    int block_number;
    QString token;
    QString url;

    ConfigSetting *setting;
};

#endif // UPLOAD_H