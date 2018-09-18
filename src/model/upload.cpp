#include "upload.h"
#include "src/util/request.h"

#include <QFileInfo>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>

#include <QDebug>

Upload::Upload(QObject *parent) : QObject(parent)
{
    setting = new ConfigSetting;
}

void Upload::setUploadConfig(QString filesPath)
{
    QFileInfo info(filesPath);
    if (info.exists()){
        file_size = info.size();
        file_name = info.fileName();
        path = "/";

        QFile file(filesPath);
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
            upload_result uploadInfo = getUploadInfo(ba);
            qDebug() << uploadInfo.code;
            qDebug() << uploadInfo.result.name;
            qDebug() << uploadInfo.result.parent;
            qDebug() << uploadInfo.result.path;
            qDebug() << uploadInfo.result.token;
            qDebug() << uploadInfo.result.type;
            qDebug() << uploadInfo.result.uploadUrl;
            qDebug() << uploadInfo.result.version;
            qDebug() << uploadInfo.status;
            qDebug() << uploadInfo.success;
            qDebug() << uploadInfo.token;
        }
        else
        {
        }
    }
}

upload_result Upload::getUploadInfo(QByteArray ba)
{
    QJsonParseError Error;
    upload_result uploadInfo;
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
        return uploadInfo;
    }
}
