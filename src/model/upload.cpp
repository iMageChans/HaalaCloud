#include "upload.h"
#include "src/util/request.h"

#include <QFileInfo>
#include <QByteArray>

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

        QByteArray ba;
        QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/user/info", setting->getSystemConfig("token"), QByteArray(), ba);
        if(ret==QNetworkReply::NoError)
        {

        }
        else
        {
        }
    }
}
