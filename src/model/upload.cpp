#include "upload.h"
#include "src/util/request.h"

#include <QFileInfo>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QCryptographicHash>
#include <QIODevice>
#include <QUuid>

#include <QDebug>

Upload::Upload(QObject *parent) : QObject(parent),
    block_size(1024 * 1024 * 4),
    bput_size(512 * 1024),
    concurrency(4)
{
    setting = new ConfigSetting;
}

void Upload::setUploadConfig(QString filesPath)
{
    QFileInfo info(filesPath);
    if (info.exists()){
        file_size = info.size();
        file_name = info.fileName();
        file_path = info.absoluteFilePath();
        path = "/";

        QFile file(file_path);
        file.open(QIODevice::ReadOnly);
        QByteArray hash = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Sha1);

        QByteArray ba;
        QJsonObject Json;
        Json.insert("name", file_name);
        Json.insert("hash", hash.toHex().constData());
        Json.insert("path","/");
        QJsonDocument docum;
        docum.setObject(Json);
        QByteArray postBa = docum.toJson(QJsonDocument::Compact);
        QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/store/token", setting->getSystemConfig("token"), postBa, ba);
        if(ret==QNetworkReply::NoError)
        {
            QUuid id = QUuid::createUuid();
            QString tmp = id.toString();
            qDebug() << tmp;
            getUploadInfo(ba);
            make_block(1);
        }
        else
        {
            qDebug() << QStringLiteral("%1 error:%2").arg("/v1/store/token").arg(ret);
        }
    }
}

void Upload::make_block(int offset)
{
    QByteArray ba;
    QString uuid;
    mlk_url(offset);

    QFile f(file_path);
    f.open(QIODevice::ReadOnly);
    QDataStream bput_file(&f);
    qDebug() << bput_file;
    auto offsets = 0;
    auto mkblk_retries = 3;
    for (int i = 0; i < file_size / block_size; ++i){
        char *buff;
        bput_file.readRawData(buff, bput_size);
        offsets += size;
        qDebug() << buff;
    }
}

void Upload::mlk_url(int offset)
{
    block_id = offset / block_size;
    if (block_id < block_number -1)
    {
        size = block_size;
    }else{
        size = int(file_size - (block_id * block_size));
    }
    block_url(size, block_id);
}

void Upload::bput_url(QString ctx, int offset)
{
    bputUrl = QString("%1/bput/%2/%3").arg(uploadInfo.result.uploadUrl).arg(ctx).arg(offset);
}

void Upload::block_url(int size, int block_num)
{
    blockUrl = QString("%1/mkblk/%2/%3").arg(uploadInfo.result.uploadUrl).arg(size).arg(block_num);
}

void Upload::file_url()
{
    fileUrl = QString("%1/mkfile/%2").arg(uploadInfo.result.uploadUrl).arg(file_size);
}

void Upload::getUploadInfo(QByteArray ba)
{
    QJsonParseError Error;
    QJsonDocument Json = QJsonDocument::fromJson(ba, &Error);
    if(Error.error == QJsonParseError::NoError){
        if(Json.isObject()){

            QJsonObject fileInfo = Json.object();
            if(fileInfo.contains("status")){
                QJsonValue status = fileInfo.value("status");
                if(status.isDouble())
                    uploadInfo.status = status.toInt();
            }

            if(fileInfo.contains("result")){
                QJsonValue result = fileInfo.value("result");
                if(result.isObject()){
                    QJsonObject Result = result.toObject();
                    if(Result.contains("name")){
                        QJsonValue name = Result.value("name");
                        if(name.isString())
                            uploadInfo.result.name = name.toString();
                    }

                    if(Result.contains("parent")){
                        QJsonValue parent = Result.value("parent");
                        if(parent.isString())
                            uploadInfo.result.parent = parent.toString();
                    }

                    if(Result.contains("token")){
                        QJsonValue token = Result.value("token");
                        if(token.isString())
                            uploadInfo.result.token = token.toString();
                    }

                    if(Result.contains("type")){
                        QJsonValue type = Result.value("type");
                        if(type.isDouble())
                           uploadInfo.result.type = type.toInt();
                    }

                    if(Result.contains("uploadUrl")){
                        QJsonValue uploadUrl = Result.value("uploadUrl");
                        if(uploadUrl.isString())
                            uploadInfo.result.uploadUrl = uploadUrl.toString();
                    }

                    if(Result.contains("version")){
                        QJsonValue version = Result.value("version");
                        if(!version.isString())
                            uploadInfo.result.version = version.toInt();
                    }
                }
            }

            if(fileInfo.contains("code")){
                QJsonValue code = fileInfo.value("code");
                if(code.isString())
                    uploadInfo.code = code.toString();
            }

            if(fileInfo.contains("success")){
                QJsonValue success = fileInfo.value("success");
                if(success.isBool())
                    uploadInfo.success = success.toBool();
            }

            if(fileInfo.contains("token")){
                QJsonValue token = fileInfo.value("token");
                if(token.isString())
                    uploadInfo.token = token.toString();
            }
        }
    }
}
