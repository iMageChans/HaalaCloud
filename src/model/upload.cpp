#include "upload.h"
#include "src/util/request.h"
#include "src/util/filesplitutils.h"

#include <QFileInfo>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QCryptographicHash>
#include <QIODevice>
#include <QUuid>

#include <QDebug>

const qint64 BUFF_SIZE_MB = 4*1024*1024;

Upload::Upload(QObject *parent) : QObject(parent),
    block_size(1024 * 1024 * 4),
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
            getUploadInfo(ba);
            Run();
        }
        else
        {
            qDebug() << QStringLiteral("%1 error:%2").arg("/v1/store/token").arg(ret);
        }
    }
}

void Upload::Run()
{
    QFile srcFile(file_path);
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    if(srcFile.open(QIODevice::ReadOnly)){
        qint64 fileSize=srcFile.size();
        qint64 mSplitSize = FileSplitUtils::getBlockFileSize();
        int splitFileNum=(fileSize+mSplitSize-1)/mSplitSize;
        qint64 count=0;
        qint64 buffSize = BUFF_SIZE_MB;
        char* buff=new char[buffSize];
        QList<BlockInfo> blocksInfo;
        for(int i=0;i<splitFileNum;i++){
            qint64 copySize=0;
            qint64 size = 0;
            copySize=fileSize-count;
            copySize=(copySize>mSplitSize)?mSplitSize:copySize;
            while(copySize>0){
                  size=(copySize>buffSize)?buffSize:copySize;
                  srcFile.read(buff,size);
                  QByteArray data = QByteArray(buff, buffSize);
                  QByteArray result;
                  QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->uploadRequest(QString("%1/mkblk/%2/%3").arg(uploadInfo.result.uploadUrl).arg(size).arg(i),
                                                                                                strId,
                                                                                                uploadInfo.result.token,
                                                                                                "application/octet-stream",
                                                                                                QString::number(size),
                                                                                                data,
                                                                                                result);
                  if(ret==QNetworkReply::NoError)
                  {
                      qDebug() << result;
                      blocksInfo.append(getMultipartUploadResult(result, i, strId));
                      copySize-=size;
                      count+=size;
                  }
                  else
                  {
                      qDebug() << QStringLiteral("%1 error:%2").arg(QString("%1/mkblk/%2/%3").arg(uploadInfo.result.uploadUrl).arg(size).arg(i)).arg(ret);
                  }
            }
        }
        delete buff;
        srcFile.close();
        QStringList ctxs;
        QStringList ctxSizes;
        for(int i=0;i<blocksInfo.length();i++){
            BlockInfo data = blocksInfo[i];
            ctxs << data.ctx;
            ctxSizes << QString::number(data.offset);
        }
        QString ctxsString = ctxs.join(",");
        QString ctxSizesString = ctxSizes.join(",");
        QByteArray data = ctxsString.toLatin1();
        QByteArray result;
        QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->uploadRequest(QString("%1/mkfile/%2").arg(uploadInfo.result.uploadUrl).arg(fileSize),
                                                                                      strId,
                                                                                      uploadInfo.result.token,
                                                                                      "text/plain",
                                                                                      ctxSizesString,
                                                                                      data,
                                                                                      result);
        if(ret==QNetworkReply::NoError)
        {
            qDebug() << result;
        }
        else
        {
            qDebug() << QStringLiteral("%1 error:%2").arg(QString("%1/mkfile/%2").arg(uploadInfo.result.uploadUrl).arg(fileSize)).arg(ret);
        }
    }
}

BlockInfo Upload::getMultipartUploadResult(QByteArray data, int i, QString uuid)
{
    BlockInfo blockInfo;
    QJsonParseError Error;
    QJsonDocument Json = QJsonDocument::fromJson(data, &Error);
    if(Error.error == QJsonParseError::NoError){
        if(Json.isObject()){

            QJsonObject fileInfo = Json.object();
            if(fileInfo.contains("ctx")){
                QJsonValue ctx = fileInfo.value("ctx");
                if(ctx.isString())
                    blockInfo.ctx = ctx.toString();
            }

            if(fileInfo.contains("checksum")){
                QJsonValue checksum = fileInfo.value("checksum");
                if(checksum.isString())
                    blockInfo.checksum = checksum.toString();
            }

            if(fileInfo.contains("crc32")){
                QJsonValue crc32 = fileInfo.value("crc32");
                if(crc32.isDouble())
                    blockInfo.crc32 = crc32.toInt();
            }

            if(fileInfo.contains("offset")){
                QJsonValue offset = fileInfo.value("offset");
                if(offset.isDouble())
                    blockInfo.offset = offset.toInt();
            }
            blockInfo.BlockNumber = i;
            blockInfo.uuid = uuid;
        }
    }
    return blockInfo;
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
